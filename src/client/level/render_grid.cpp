#include "render_grid.hpp"

namespace client {
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs) {
		auto size = grid.size();
		float cell_size = 1.f; 

		sf::RectangleShape frame;
		frame.setSize({static_cast<float>(size.x), static_cast<float>(size.y)}),
		frame.setOutlineColor(sf::Color::Red);
		frame.setFillColor(sf::Color::Transparent);
		frame.setPosition(0,0);
		frame.setOutlineThickness(1.f);
		target.draw(frame);

		sf::VertexArray vertecies;
		vertecies.setPrimitiveType(sf::Quads);
		for(std::size_t x = 0; x < size.x; ++x) {
			for(std::size_t y = 0; y < size.y; ++y) {
				auto id = grid(x,y);
				if(id >= 256) {
					vertecies.append(sf::Vertex{{cell_size * (x+0), cell_size * (y+0)}, sf::Color::White});
					vertecies.append(sf::Vertex{{cell_size * (x+1), cell_size * (y+0)}, sf::Color::White});
					vertecies.append(sf::Vertex{{cell_size * (x+1), cell_size * (y+1)}, sf::Color::White});
					vertecies.append(sf::Vertex{{cell_size * (x+0), cell_size * (y+1)}, sf::Color::White});
				}
			}
		}
		target.draw(vertecies);
	}
}