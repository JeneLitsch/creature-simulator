#include "PlaceFood.hpp"
#include "sim/Simulation.hpp"
#include "sim/create.hpp"

namespace client::edit {
	void PlaceFood::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid[stx::vector2u{position}] == 0) {
			sim::create_food(ecs, stx::vector2i{position}, grid);
		}
	}



	void PlaceFood::clean_up(sim::Simulation & sim) {
		
	}
}