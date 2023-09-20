#include "PlaceEntity.hpp"
#include "sim/Simulation.hpp"
#include "sim/create.hpp"

namespace client::edit {
	void PlaceEntity::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid.in_range(position) && grid[position] == 0) {
			sim::create_creature(ecs, stx::vector2i{position}, grid, sim.config, 5.0);
		}
	}



	void PlaceEntity::clean_up(sim::Simulation & sim) {
		
	}
}