#include "generate.hpp"
#include "create.hpp"
#include <queue>
#include "stdxx/random.hxx"
#include "xoshiro256.h"

namespace sim {
	namespace {
		struct State {
            Xoshiro::Xoshiro256PP rng;
			std::uniform_int_distribution<std::uint32_t> dist_x;
			std::uniform_int_distribution<std::uint32_t> dist_y;
		};



		void generate_obstacles(const ObstaclePreset::None &, Simulation & sim, State &) {}
		
		

		
		void generate_obstacles(const ObstaclePreset::Rocks & rocks, Simulation & sim, State & state) {
			const auto size = sim.grid.size();
			struct Cell { bool wall = false; };

			stx::grid2<Cell> cell_map{size, Cell {
				.wall = false
			}};

			stx::grid2<Cell> new_cell_map = cell_map;
			for(std::uint32_t i = 0; i < rocks.cores; ++i) {
				const auto x = state.dist_x(state.rng);
				const auto y = state.dist_y(state.rng);
				cell_map(x,y).wall = true;
			}

			for(std::uint32_t i = 0; i < rocks.build_up; ++i) {
				for(std::uint32_t x = 0; x < size.x; ++x) {
					for(std::uint32_t y = 0; y < size.y; ++y) {
						const bool n = cell_map.in_range(x    , y - 1) && cell_map(x    , y - 1).wall;
						const bool e = cell_map.in_range(x + 1, y    ) && cell_map(x + 1, y    ).wall;
						const bool s = cell_map.in_range(x    , y + 1) && cell_map(x    , y + 1).wall;
						const bool w = cell_map.in_range(x - 1, y    ) && cell_map(x - 1, y    ).wall;
						const bool neighbors_barrier = (n || e || s || w); 
						if(neighbors_barrier && (state.rng() % 2 != 0)) {
							new_cell_map(x,y).wall = true;
						}
					}
				}

				cell_map = new_cell_map;
			}

			for(std::uint32_t x = 0; x < size.x; ++x) {
				for(std::uint32_t y = 0; y < size.y; ++y) {
					if(cell_map(x,y).wall) {
						create_barrier(sim.ecs, stx::vector2i{static_cast<std::int32_t>(x),static_cast<std::int32_t>(y)}, sim.grid);
					}
				}
			}
		}
	}


	std::unique_ptr<Simulation> generate(const WorldPreset & preset) {
		auto sim = Simulation::empty(preset.size);

		sim->rng.seed(preset.seed);

		State state {
            .rng = Xoshiro::Xoshiro256PP(sim->rng()),
			.dist_x = std::uniform_int_distribution<std::uint32_t> {0, static_cast<std::uint32_t>(preset.size.x) - 1},
			.dist_y = std::uniform_int_distribution<std::uint32_t> {0, static_cast<std::uint32_t>(preset.size.y) - 1},
		};


		for(std::uint64_t i = 0; i < preset.entities.empty_creatures; i++) {
			const auto x = state.dist_x(state.rng);
			const auto y = state.dist_y(state.rng);
			if(sim->grid(x,y) == 0) {
				create_creature(sim->ecs, stx::vector2i{static_cast<std::int32_t>(x),static_cast<std::int32_t>(y)}, sim->grid, sim->config, 5.0);
			}
		}

		for(std::uint64_t i = 0; i < preset.entities.food_spawners; i++) {
			const auto x = state.dist_x(state.rng);
			const auto y = state.dist_y(state.rng);
			if(sim->grid(x,y) == 0) {
				create_food_spawner(sim->ecs, stx::vector2i{static_cast<std::int32_t>(x),static_cast<std::int32_t>(y)}, sim->grid);
			}
		}




		std::visit([&] (auto & policy) { return generate_obstacles(policy, *sim, state); }, preset.obstacles.policy);

		return sim;
	}
}
