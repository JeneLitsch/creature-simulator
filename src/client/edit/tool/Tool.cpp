#include "Tool.hpp"
#include "imgui.h"

#include "shape/Rect.hpp"
#include "shape/Point.hpp"

#include "effect/Erase.hpp"
#include "effect/EmptyEntity.hpp"
#include "effect/Barrier.hpp"

namespace client::edit {
	void Tool::draw(sim::Simulation & sim, stx::position2i position) {
		this->shape->apply(position, [&] (stx::position2i position) {
			this->effect->apply(sim, position);
		});
		this->effect->clean_up(sim);
	}



	void Tool::render(sf::RenderTarget & target, stx::position2i position) {
		this->shape->render(target, position);
	}



	void Tool::ui() {
		ImGui::Text(this->name.c_str());
		this->shape->ui();
	}



	Tool Tool::eraser() {
		return Tool {
			.name = "Eraser",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<Erase>(),
		};
	}	



	Tool Tool::barrier() {
		return Tool {
			.name = "Barrier",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<Barrier>(),
		};
	}	



	Tool Tool::place_entity() {
		return Tool {
			.name = "Empty Entity",
			.shape = std::make_unique<Point>(),
			.effect = std::make_unique<EmptyEntity>(),
		};
	}	
}