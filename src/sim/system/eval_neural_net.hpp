#pragma once
#include "sim/Ecs.hpp"

namespace sim {
	void eval_neural(Ecs::Entity & entity, const Config& config, double oscilator_short, double oscilator_long);
}