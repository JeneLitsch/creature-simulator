#pragma once
#include "Tool.hpp"
#include "Rect.hpp"

namespace client::edit {
	struct Eraser : public Tool {
		virtual void apply(sim::Simulation & sim, stx::position2i position) override;
		virtual void ui() override;
		virtual void render(sf::RenderTarget &, stx::position2i) override;

		Rect rect;
	};	
}