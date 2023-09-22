#include "PlaceFoodSpawner.hpp"
#include "sim/Simulation.hpp"
#include "sim/create.hpp"

namespace client::edit {
	void PlaceFoodSpawner::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid[stx::vector2u{position}] == 0) {
			sim::create_food_spawner(ecs, stx::vector2i{position}, grid);
		}
	}



	void PlaceFoodSpawner::clean_up(sim::Simulation & sim) {
		
	}
}