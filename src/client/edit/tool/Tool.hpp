#pragma once
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"

namespace sim {
	class Simulation;
}

namespace client::edit {
	struct Tool {
		Tool() {}
		virtual ~Tool() = default;
		virtual void apply(sim::Simulation & sim, stx::position2i) = 0;
		virtual void ui() = 0;
		virtual void render(sf::RenderTarget &, stx::position2i) = 0;
	};	
}