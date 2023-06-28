#pragma once
#include "sim/Ecs.hpp"

namespace sim {
	class Simulation;
	void move(Ecs::Entity & entity, Ecs & ecs, Simulation& simulation);
}