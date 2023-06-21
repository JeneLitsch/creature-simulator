#pragma once
#include <random>
#include "sim/Ecs.hpp"

namespace sim{
	void spawn_food(Ecs::Entity & entity, stx::grid2<std::uint64_t> & grid, Ecs & ecs, std::mt19937_64 & rng, PheromoneField & phero_field);
}