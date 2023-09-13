#pragma once
#include "Simulation.hpp"

namespace sim {
	std::unique_ptr<Simulation> generate(const WorldPreset & preset);
}