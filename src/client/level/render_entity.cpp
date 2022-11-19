#include "render_entity.hpp"

namespace client::level {
	void render_entity(sf::VertexArray & vertecies, const Ecs::Entity & entity) {
		if(!entity.has<Sprite>()) return;
		if(!entity.has<Position>()) return;
		if(!entity.has<Rotation>()) return;

		auto & sprite = entity.get<Sprite>();
		auto & position = entity.get<Position>();
		auto & rotation = entity.get<Rotation>();

		sf::Transform transform;
		transform.translate(position.position.x, position.position.y);
		transform.rotate(rotation.angle);

		const float x1 = -10;
		const float x2 = +10;
		const float y1 = -10;
		const float y2 = +10;

		const auto vertex1 = transform.transformPoint(x1,y1);
		const auto vertex2 = transform.transformPoint(x2,y1);
		const auto vertex3 = transform.transformPoint(x2,y2);
		const auto vertex4 = transform.transformPoint(x1,y2);

		vertecies.append(sf::Vertex{vertex1, sf::Color::White});
		vertecies.append(sf::Vertex{vertex2, sf::Color::White});
		vertecies.append(sf::Vertex{vertex3, sf::Color::White});
		vertecies.append(sf::Vertex{vertex4, sf::Color::White});
	}
}