#pragma once
#include <span>
#include "stdxx/grid.hxx"
#include "sim/Ecs.hpp"
#include "sim/senses/PheromoneField.hpp"
#include "SFML/Graphics.hpp"

namespace client {
	void render_frame(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, sim::Ecs & ecs);
	void render_grid(sf::RenderTarget & target, const stx::grid2<std::uint64_t> & grid, sim::Ecs & ecs);
	void render_phermones(sf::RenderTarget & target, const sim::PheromoneField & field); 
}