#include "Petrify.hpp"
#include "sim/Simulation.hpp"
#include "sim/create.hpp"

namespace client::edit {
	void Petrify::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid.in_range(position)) {
			auto id = std::exchange(grid[position], 0);
			if(auto * entity = ecs.get_if(id)) {
				entity->mark_delete();
				sim::create_barrier(ecs, stx::vector2i{position}, grid);
			}
		}
	}



	void Petrify::clean_up(sim::Simulation & sim) {
		sim.get_ecs().clean_up();
	}
}