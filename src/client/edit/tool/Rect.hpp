#pragma once
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"

namespace client::edit {
	struct Rect {
		void operator()(stx::position2i32 position, auto sample) {
			for(std::int32_t x = -this->radius; x <= this->radius; ++x) {
				for(std::int32_t y = -this->radius; y <= this->radius; ++y) {
					sample(position + stx::position2i32{x,y});
				}
			}
		}

		void render(sf::RenderTarget & target, stx::position2i position) {
			sf::VertexArray vertecies;

			vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y-radius)}, sf::Color::White});
			vertecies.append(sf::Vertex{{1.f * (position.x+radius+1), 1.f * (position.y-radius)}, sf::Color::White});
			vertecies.append(sf::Vertex{{1.f * (position.x+radius+1), 1.f * (position.y+radius+1)}, sf::Color::White});
			vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y+radius+1)}, sf::Color::White});
			vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y-radius)}, sf::Color::White});
			
			vertecies.setPrimitiveType(sf::LineStrip);
			target.draw(vertecies);
		}

		std::int32_t radius = 1;
	};
}