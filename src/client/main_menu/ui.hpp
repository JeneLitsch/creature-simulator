#pragma once
#include <random>
#include "shared/random/xoshiro256.h"
#include "sim/WorldPreset.hpp"

namespace client::main_menu {
	void ui_world(sim::WorldPreset & preset, Xoshiro::Xoshiro256PP & rng);
	void ui_entities(sim::WorldPreset & preset);
	void ui_obstacles(sim::ObstaclePreset & preset, int & radio_index);
}
