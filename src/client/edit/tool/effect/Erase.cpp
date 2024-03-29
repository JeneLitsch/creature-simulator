#include "Erase.hpp"
#include "sim/Simulation.hpp"

namespace client::edit {
	void Erase::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		auto id = std::exchange(grid[stx::vector2u{position}], 0);
		if(auto * entity = ecs.get_if(id)) {
			entity->mark_delete();
		}
	}



	void Erase::clean_up(sim::Simulation & sim) {
		sim.get_ecs().clean_up();
	}
}