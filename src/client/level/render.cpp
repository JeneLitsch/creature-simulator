#include "render.hpp"

namespace client {
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs) {
		auto size = grid.size();
		float cell_size = 1.f; 
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



	void render_frame(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs) {
		auto size = grid.size();
		sf::RectangleShape frame;
		frame.setSize({static_cast<float>(size.x), static_cast<float>(size.y)}),
		frame.setOutlineColor(sf::Color::Red);
		frame.setFillColor(sf::Color::Transparent);
		frame.setPosition(0,0);
		frame.setOutlineThickness(1.f);
		target.draw(frame);
	}



	void render_phermones(sf::RenderTarget & target, const stx::grid2<float> & field, sf::Color color) {
		auto size = field.size();
		float cell_size = 1.f; 
		sf::VertexArray vertecies;
		vertecies.setPrimitiveType(sf::Quads);
		for(std::size_t x = 0; x < size.x; ++x) {
			for(std::size_t y = 0; y < size.y; ++y) {
				const std::uint8_t brightness = static_cast<std::uint8_t>(255 * field(x,y));
				const sf::Color final_color = color * sf::Color{brightness, brightness, brightness};
				vertecies.append(sf::Vertex{{cell_size * (x+0), cell_size * (y+0)}, final_color});
				vertecies.append(sf::Vertex{{cell_size * (x+1), cell_size * (y+0)}, final_color});
				vertecies.append(sf::Vertex{{cell_size * (x+1), cell_size * (y+1)}, final_color});
				vertecies.append(sf::Vertex{{cell_size * (x+0), cell_size * (y+1)}, final_color});
			}
		}
		target.draw(vertecies, sf::BlendAdd);
	}
}