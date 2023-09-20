#pragma once
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"
#include "shape/Shape.hpp"
#include "effect/Effect.hpp"

namespace sim {
	class Simulation;
}

namespace client::edit {
	struct Tool {
		void draw(sim::Simulation & sim, stx::position2i);
		void ui();
		void render(sf::RenderTarget &, stx::position2i);

		std::string name;
		std::unique_ptr<Shape> shape;
		std::unique_ptr<Effect> effect;

		static Tool eraser();	
		static Tool barrier();	
		static Tool place_entity();	
	};


}