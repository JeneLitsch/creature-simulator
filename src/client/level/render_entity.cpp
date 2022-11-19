#include "render_entity.hpp"

namespace client::level {
	void render_entity(sf::VertexArray & vertecies, const Ecs::Entity & entity) {
		if(!entity.has<Sprite>()) return;
		if(!entity.has<Position>()) return;

		auto & sprite = entity.get<Sprite>();
		auto & position = entity.get<Position>();

		const float x0 = position.position.x;
		const float y0 = position.position.y;
		const float x1 = x0 - 10.f;
		const float x2 = x0 + 10.f;
		const float y1 = y0 - 10.f;
		const float y2 = y0 + 10.f;

		vertecies.append(sf::Vertex{{x1,y1}, sf::Color::White});
		vertecies.append(sf::Vertex{{x2,y1}, sf::Color::White});
		vertecies.append(sf::Vertex{{x2,y2}, sf::Color::White});
		vertecies.append(sf::Vertex{{x1,y2}, sf::Color::White});
	}
}