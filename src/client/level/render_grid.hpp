#pragma once
#include "stdxx/grid.hxx"
#include "server/Ecs.hpp"
#include "SFML/Graphics.hpp"

namespace client {
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs);
}