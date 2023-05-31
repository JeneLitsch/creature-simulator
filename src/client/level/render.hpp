#pragma once
#include <span>
#include "stdxx/grid.hxx"
#include "server/Ecs.hpp"
#include "SFML/Graphics.hpp"

namespace client {
	void render_frame(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs);
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, server::Ecs & ecs);
	void render_phermones(sf::RenderTarget & target, const stx::grid2<float> & field, sf::Color color); 
}