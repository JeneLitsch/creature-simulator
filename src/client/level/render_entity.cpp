#include "render_entity.hpp"
#include "stdxx/math.hxx"

namespace client::level {
	void render_entity(const Ecs::Entity & entity, sf::VertexArray & vertecies) {
		if(!entity.has<Sprite>()) return;
		if(!entity.has<Transform>()) return;

		auto & sprite = entity.get<Sprite>();
		auto & transform = entity.get<Transform>();

		auto pos = stx::lerp(transform.position_prev, transform.position_next, transform.t);
		auto rot = stx::lerp(transform.rotation_prev, transform.rotation_next, transform.t);

		sf::Transform sf_transform;
		sf_transform.translate(pos.x, pos.y);
		sf_transform.rotate(rot);

		const int tx1 = sprite.tex_position.x;
		const int ty1 = sprite.tex_position.y;
		const int tx2 = tx1 + sprite.tex_size.x;
		const int ty2 = ty1 + sprite.tex_size.y;

		const float vx1 = -static_cast<float>(sprite.tex_size.x);
		const float vx2 = +static_cast<float>(sprite.tex_size.x);
		const float vy1 = -static_cast<float>(sprite.tex_size.y);
		const float vy2 = +static_cast<float>(sprite.tex_size.y);

		const auto vertex1 = sf_transform.transformPoint(vx1, vy1);
		const auto vertex2 = sf_transform.transformPoint(vx2, vy1);
		const auto vertex3 = sf_transform.transformPoint(vx2, vy2);
		const auto vertex4 = sf_transform.transformPoint(vx1, vy2);

		const sf::Vector2f tex1 {static_cast<float>(tx1), static_cast<float>(ty1)};
		const sf::Vector2f tex2 {static_cast<float>(tx2), static_cast<float>(ty1)};
		const sf::Vector2f tex3 {static_cast<float>(tx2), static_cast<float>(ty2)};
		const sf::Vector2f tex4 {static_cast<float>(tx1), static_cast<float>(ty2)};

		vertecies.append(sf::Vertex{vertex1, sf::Color::White, tex1});
		vertecies.append(sf::Vertex{vertex2, sf::Color::White, tex2});
		vertecies.append(sf::Vertex{vertex3, sf::Color::White, tex3});
		vertecies.append(sf::Vertex{vertex4, sf::Color::White, tex4});
	}
}