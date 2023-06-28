#pragma once
#include "sim/Ecs.hpp"

namespace sim {
    class Simulation;
	void check_death(Ecs::Entity & entity, Simulation& simulation, const Config& config);
}