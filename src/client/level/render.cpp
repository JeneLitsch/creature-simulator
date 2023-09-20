#include "render.hpp"

namespace client {
	constexpr static float cell_size = 1.f; 

	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, const sim::Ecs & ecs) {
		sf::VertexArray vertecies;
		vertecies.setPrimitiveType(sf::Quads);
		ecs.run_system([&] (const sim::Ecs::Entity & entity) {
			auto * sprite = entity.get_if<sim::Sprite>();
			const sf::Color color = sprite ? sprite->color : sf::Color::White;
			if(auto * tr = entity.get_if<sim::Transform>()) {
				vertecies.append(sf::Vertex{{cell_size * (tr->location.x+0), cell_size * (tr->location.y+0)}, color});
				vertecies.append(sf::Vertex{{cell_size * (tr->location.x+1), cell_size * (tr->location.y+0)}, color});
				vertecies.append(sf::Vertex{{cell_size * (tr->location.x+1), cell_size * (tr->location.y+1)}, color});
				vertecies.append(sf::Vertex{{cell_size * (tr->location.x+0), cell_size * (tr->location.y+1)}, color});
			}
		});
		target.draw(vertecies);
	}



	void render_frame(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, const sim::Ecs & ecs) {
		auto size = grid.size();
		sf::RectangleShape frame;
		frame.setSize({static_cast<float>(size.x), static_cast<float>(size.y)}),
		frame.setOutlineColor(sf::Color::Red);
		frame.setFillColor(sf::Color::Transparent);
		frame.setPosition(0,0);
		frame.setOutlineThickness(1.f);
		target.draw(frame);
	}
}