#include "Point.hpp"
#include "imgui.h"

namespace client::edit {
	void Point::apply(stx::position2i32 position, std::function<void(stx::position2i32)> sample) {
		sample(position);
	}

	void Point::render(sf::RenderTarget & target, stx::position2i position) const {
		sf::VertexArray vertecies;
		const float x = static_cast<float>(position.x);
		const float y = static_cast<float>(position.y);
		vertecies.append(sf::Vertex{{x+0.f, y+0.f}, sf::Color::White});
		vertecies.append(sf::Vertex{{x+1.f, y+0.f}, sf::Color::White});
		vertecies.append(sf::Vertex{{x+1.f, y+1.f}, sf::Color::White});
		vertecies.append(sf::Vertex{{x+0.f, y+1.f}, sf::Color::White});
		vertecies.append(sf::Vertex{{x+0.f, y+0.f}, sf::Color::White});
		
		vertecies.setPrimitiveType(sf::LineStrip);
		target.draw(vertecies);
	}

	void Point::ui() {}
}