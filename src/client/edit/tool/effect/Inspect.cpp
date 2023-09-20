#include "Inspect.hpp"
#include "sim/Simulation.hpp"
#include "client/edit/Edit.hpp"

namespace client::edit {
	Inspect::Inspect(stx::reference<Edit> edit) 
		: edit{edit} {}



	void Inspect::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		if(grid.in_range(position) && grid[position]) {
			this->edit->inspect(grid[position]);
		}
	}



	void Inspect::clean_up(sim::Simulation & sim) {

	}




}