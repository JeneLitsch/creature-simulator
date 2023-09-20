#pragma once
#include "Shape.hpp"

namespace client::edit {
	struct Point : Shape {
		virtual void apply(stx::position2i32 position, std::function<void(stx::position2i32)> sample) override;
		virtual void render(sf::RenderTarget & target, stx::position2i position) const override;
		virtual void ui() override;
	};
}