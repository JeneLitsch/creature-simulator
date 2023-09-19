#include "Eraser.hpp"
#include "sim/Simulation.hpp"
#include "imgui.h"

namespace client::edit {
	void Eraser::apply(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		auto & ecs = sim.get_ecs();
		this->rect(position, [&] (stx::position2i position) {
			if(grid.in_range(position)) {
				auto id = std::exchange(grid[position], 0); 
				if(auto * entity = ecs.get_if(id)) {
					entity->mark_delete();
				}
			}
		});
		ecs.clean_up();
	}



	void Eraser::ui() {
		ImGui::Text("Eraser");
		ImGui::SliderInt("Radius", &this->rect.radius, 0, 10);
	}



	void Eraser::render(sf::RenderTarget & target, stx::position2i position) {
		this->rect.render(target, position);
	}
}