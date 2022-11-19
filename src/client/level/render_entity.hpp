#pragma once
#include <SFML/Graphics.hpp>
#include "client/level/Ecs.hpp"

namespace client::level {
	void render_entity(sf::VertexArray & vertecies, const Ecs::Entity & entity);
}