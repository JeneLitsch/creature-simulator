#include "Point.hpp"
#include "imgui.h"

namespace client::edit {
	void Point::apply(stx::position2i32 position, std::function<void(stx::position2i32)> sample) {
		sample(position);
	}

	void Point::render(sf::RenderTarget & target, stx::position2i position) const {
		sf::VertexArray vertecies;

		vertecies.append(sf::Vertex{{1.f * (position.x+0), 1.f * (position.y+0)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+1), 1.f * (position.y+0)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+1), 1.f * (position.y+1)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+0), 1.f * (position.y+1)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+0), 1.f * (position.y+0)}, sf::Color::White});
		
		vertecies.setPrimitiveType(sf::LineStrip);
		target.draw(vertecies);
	}

	void Point::ui() {}
}