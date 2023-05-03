#pragma once
#include <random>
#include "server/Ecs.hpp"

namespace server {
	void move_randomly(Ecs::Entity & entity, double dt, std::mt19937_64 & rng);
}