#include "PheromoneField.hpp"

namespace sim {
	namespace {
		void init_buffer(sf::RenderTexture & buffer, stx::size2u size) {
			buffer.create(size.x, size.y);
			buffer.clear(sf::Color::Black);
			buffer.display();
		}
	}

	PheromoneField::PheromoneField(stx::size2u size) {
		init_buffer(this->buffer_raw, size);
		init_buffer(this->buffer_blur_h, size);
		init_buffer(this->buffer_blur_v, size);
		init_buffer(this->buffer_final, size);

		this->shader_blur_h.loadFromFile("assets/shader/blur_h.vert", "assets/shader/blur.frag");
		this->shader_blur_h.setUniform("tex", sf::Shader::CurrentTexture);
		this->shader_blur_h.setUniform("width", static_cast<float>(size.x));
		this->shader_blur_v.loadFromFile("assets/shader/blur_v.vert", "assets/shader/blur.frag");
		this->shader_blur_v.setUniform("tex", sf::Shader::CurrentTexture);
		this->shader_blur_v.setUniform("height", static_cast<float>(size.y));
	}



	void PheromoneField::swap() {
		this->toggle = !this->toggle;
	}



	void PheromoneField::emit(stx::position2i position, int radius, sf::Color composition) {
		sf::CircleShape circle;
		circle.setRadius(radius);
		circle.setOrigin(radius, radius);
		circle.setPosition(position.x, position.y);
		circle.setFillColor(composition);
		this->buffer_raw.draw(circle, sf::BlendAdd);
	}



	namespace {
		sf::RectangleShape make_rect(const sf::RenderTexture & tex, sf::Color color = sf::Color::White) {
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f{tex.getSize()});
			rect.setPosition(0,0);
			rect.setTexture(&tex.getTexture());
			rect.setFillColor(color);
			return rect;
		}
	}




	void PheromoneField::display() {
		this->buffer_raw.display();
		this->buffer_blur_v.draw(make_rect(this->buffer_raw), &this->shader_blur_v);
		this->buffer_blur_v.display();
		this->buffer_blur_h.draw(make_rect(this->buffer_blur_v), &this->shader_blur_h);
		this->buffer_blur_h.display();
		this->buffer_final.draw(make_rect(this->buffer_blur_h, sf::Color{250,250,250}));
		this->buffer_final.display();
		this->buffer_raw.draw(make_rect(this->buffer_final));

		this->read_buffer = this->buffer_final.getTexture().copyToImage();
	}



	const sf::Texture & PheromoneField::get_texture() const {
		return this->buffer_final.getTexture();
	}
}