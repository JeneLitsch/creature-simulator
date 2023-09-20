#pragma once
#include "sim/Ecs.hpp"

namespace client::edit {
	void ui_inspect(sim::Ecs::Entity & entity, sf::RenderTexture & neural_network_graph);
}