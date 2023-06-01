#pragma once
#include "SFML/Graphics.hpp"
#include "stdxx/math.hxx"

namespace server {
	class PheromoneField {
	public:
		PheromoneField(stx::size2u size);

		void swap();
		void emit(stx::position2i position, int radius, sf::Color composition);
		void display();

		const sf::Texture & get_texture() const;

	private:
		std::array<sf::RenderTexture, 2> double_buffer;
		sf::Image read_buffer;
		sf::Shader dispersion;
		bool toggle = false;
		double stability = 0.9;
	};
}