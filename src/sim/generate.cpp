#include "generate.hpp"
#include "create.hpp"

namespace sim {
	namespace {

	}


	std::unique_ptr<Simulation> generate(const WorldPreset & preset) {
		auto sim = Simulation::empty(preset.size);

		sim->rng.seed(42);

		std::uniform_int_distribution<std::int32_t> dist_x {0, static_cast<std::int32_t>(preset.size.x) - 1};
		std::uniform_int_distribution<std::int32_t> dist_y {0, static_cast<std::int32_t>(preset.size.y) - 1};

		for(std::uint64_t i = 0; i < preset.entities.empty_creatures; i++) {
			const auto x = dist_x(sim->rng);
			const auto y = dist_y(sim->rng);
			if(sim->grid(x,y) == 0) {
				create_creature(sim->ecs, stx::vector2i{x, y}, sim->grid, sim->config, 5.0);
			}
		}

		for(std::uint64_t i = 0; i < preset.entities.food_spawners; i++) {
			const auto x = dist_x(sim->rng);
			const auto y = dist_y(sim->rng);
			if(sim->grid(x,y) == 0) {
				create_food_spawner(sim->ecs, stx::vector2i{x,y}, sim->grid);
			}
		}

		for(std::uint64_t i = 0; i < preset.barriers; i++) {
			const auto x = dist_x(sim->rng);
			const auto y = dist_y(sim->rng);
			if(sim->grid(x,y) == 0) {
				create_barrier(sim->ecs, stx::vector2i{x,y}, sim->grid);
			}
		}

		return sim;
	}
}