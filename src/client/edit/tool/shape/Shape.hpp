#pragma once
#include <functional>
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"

namespace client::edit {
	class Shape {
	public:
		virtual void apply(stx::position2i32 position, std::function<void(stx::position2i32)> sample) = 0;
		virtual void render(sf::RenderTarget & target, stx::position2i position) const = 0;
		virtual void ui() = 0;
	};
}