#pragma once
#include <random>
#include "Ecs.hpp"

namespace client::level {
	void move_randomly(Ecs::Entity & entity, double dt, std::mt19937_64 & rng);
}