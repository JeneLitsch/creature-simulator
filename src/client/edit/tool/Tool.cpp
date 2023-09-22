#include "Tool.hpp"
#include "imgui.h"
#include "client/edit/Edit.hpp"
#include "sim/Simulation.hpp"

#include "shape/Rect.hpp"
#include "shape/Point.hpp"

#include "effect/Erase.hpp"
#include "effect/PlaceEmptyCreature.hpp"
#include "effect/PlaceFoodSpawner.hpp"
#include "effect/PlaceFood.hpp"
#include "effect/Barrier.hpp"
#include "effect/Inspect.hpp"
#include "effect/Petrify.hpp"

namespace client::edit {
	void Tool::draw(sim::Simulation & sim, stx::position2i position) {
		auto & grid = sim.get_grid();
		this->shape->apply(position, [&] (stx::position2i position) {
			if(position.x < 0) return;
			if(position.y < 0) return;
			if(grid.in_range(stx::vector2u{position})) {
				this->effect->apply(sim, position);
			}
		});
		this->effect->clean_up(sim);
	}



	void Tool::render(sf::RenderTarget & target, stx::position2i position) {
		this->shape->render(target, position);
	}



	void Tool::ui() {
		ImGui::Text("%s", this->name.c_str());
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



	Tool Tool::place_empty_creature() {
		return Tool {
			.name = "Empty Creature",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<PlaceEmptyCreature>(),
		};
	}



	Tool Tool::place_food_spawner() {
		return Tool {
			.name = "Food Spawner",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<PlaceFoodSpawner>(),
		};
	}



	Tool Tool::place_food() {
		return Tool {
			.name = "Food",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<PlaceFood>(),
		};
	}


	
	Tool Tool::inspector(stx::reference<Edit> edit) {
		return Tool {
			.name = "Inspector",
			.shape = std::make_unique<Point>(),
			.effect = std::make_unique<Inspect>(edit),
		};
	}



	Tool Tool::medusa() {
		return Tool {
			.name = "Medusa",
			.shape = std::make_unique<Rect>(),
			.effect = std::make_unique<Petrify>(),
		};
	}
}