#pragma once
#include <span>
#include "stdxx/grid.hxx"
#include "sim/Ecs.hpp"
#include "SFML/Graphics.hpp"

namespace client {
	void render_frame(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, const sim::Ecs & ecs);
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, const sim::Ecs & ecs);
}