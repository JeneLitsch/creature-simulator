#include "Rect.hpp"
#include "imgui.h"

namespace client::edit {
	void Rect::apply(stx::position2i32 position, std::function<void(stx::position2i32)> sample) {
		for(std::int32_t x = -this->radius; x <= this->radius; ++x) {
			for(std::int32_t y = -this->radius; y <= this->radius; ++y) {
				sample(position + stx::position2i32{x,y});
			}
		}
	}

	void Rect::render(sf::RenderTarget & target, stx::position2i position) const {
		sf::VertexArray vertecies;

		vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y-radius)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+radius+1), 1.f * (position.y-radius)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x+radius+1), 1.f * (position.y+radius+1)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y+radius+1)}, sf::Color::White});
		vertecies.append(sf::Vertex{{1.f * (position.x-radius), 1.f * (position.y-radius)}, sf::Color::White});
		
		vertecies.setPrimitiveType(sf::LineStrip);
		target.draw(vertecies);
	}

	void Rect::ui() {
		ImGui::SliderInt("Radius", &this->radius, 0, 10);
	}
}