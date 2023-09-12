#pragma once
#include "SFML/Graphics.hpp"
#include "stdxx/math.hxx"

namespace sim {
	class PheromoneField {
	public:
		PheromoneField(stx::size2u size);

		void swap();
		void emit(stx::position2i position, int radius, sf::Color composition);
		void display();

		const sf::Texture & get_texture() const;

		void set_data( const std::vector<std::uint8_t> & bytes);

	private:
		sf::RenderTexture buffer_raw;
		sf::RenderTexture buffer_blur_h;
		sf::RenderTexture buffer_blur_v;
		sf::RenderTexture buffer_final;

		sf::Image read_buffer;

		sf::Shader shader_blur_h;
		sf::Shader shader_blur_v;
		
		bool toggle = false;
		double stability = 0.9;
	};
}