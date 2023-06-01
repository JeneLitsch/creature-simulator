#include "PheromoneField.hpp"

namespace server {
	PheromoneField::PheromoneField(stx::size2u size) {
		for(auto & tex : this->double_buffer) {
			tex.create(size.x, size.y);
			tex.clear(sf::Color::Black);
			tex.display();
		}
		this->dispersion.loadFromMemory("assets/shaders/blur.frag", sf::Shader::Type::Fragment);
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
		auto & source = this->double_buffer[this->toggle];
		source.draw(circle, sf::BlendAdd);
	}



	namespace {
		void disperse(sf::RenderTexture & target, const sf::Texture & source, double stability) {
			std::uint8_t fade = static_cast<std::uint8_t>(stability * 255);
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f{target.getSize()});
			rect.setPosition(0,0);
			rect.setTexture(&source);
			rect.setFillColor(sf::Color{fade,fade,fade});
			target.draw(rect);
		}
	}



	void PheromoneField::display() {
		auto & source = this->double_buffer[this->toggle];
		auto & target = this->double_buffer[!this->toggle];
		source.display();
		disperse(target, source.getTexture(), this->stability);
		target.display();
		this->read_buffer = target.getTexture().copyToImage();
	}



	const sf::Texture & PheromoneField::get_texture() const {
		return this->double_buffer[this->toggle].getTexture();
	}
}