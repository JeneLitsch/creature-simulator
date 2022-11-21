#pragma once
#include <SFML/Graphics.hpp>
#include "client/level/Ecs.hpp"

namespace client::level {
	void render_entity(const Ecs::Entity & entity, sf::VertexArray & vertecies);
}