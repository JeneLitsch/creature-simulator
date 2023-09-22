#include "Inspect.hpp"
#include "sim/Simulation.hpp"
#include "client/edit/Edit.hpp"

namespace client::edit {
	Inspect::Inspect(stx::reference<Edit> edit) 
		: edit{edit} {}



	void Inspect::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		if(grid[stx::vector2u{position}]) {
			this->edit->inspect(grid[stx::vector2u{position}]);
		}
	}



	void Inspect::clean_up(sim::Simulation & sim) {

	}




}