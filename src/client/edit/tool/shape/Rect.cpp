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
		const float x = static_cast<float>(position.x);
		const float y = static_cast<float>(position.y);
		const float radius_f = static_cast<float>(this->radius);
		vertecies.append(sf::Vertex{{x-radius_f  , y-radius_f  }, sf::Color::White});
		vertecies.append(sf::Vertex{{x+radius_f+1, y-radius_f  }, sf::Color::White});
		vertecies.append(sf::Vertex{{x+radius_f+1, y+radius_f+1}, sf::Color::White});
		vertecies.append(sf::Vertex{{x-radius_f  , y+radius_f+1}, sf::Color::White});
		vertecies.append(sf::Vertex{{x-radius_f  , y-radius_f  }, sf::Color::White});
		
		vertecies.setPrimitiveType(sf::LineStrip);
		target.draw(vertecies);
	}



	void Rect::ui() {
		ImGui::SliderInt("Radius", &this->radius, 0, 10);
	}
}