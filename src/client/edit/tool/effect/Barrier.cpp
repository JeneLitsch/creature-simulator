#include "Barrier.hpp"
#include "sim/Simulation.hpp"
#include "imgui.h"
#include "sim/create.hpp"

namespace client::edit {
	void Barrier::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid.in_range(position) && grid[position] == 0) {
			sim::create_barrier(ecs, stx::vector2i{position}, grid);
		}
	}



	void Barrier::clean_up(sim::Simulation & sim) {

	}
}