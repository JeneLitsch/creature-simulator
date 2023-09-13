#pragma once
#include <random>
#include "sim/WorldPreset.hpp"

namespace client::main_menu {
	void ui_world(sim::WorldPreset & preset, std::mt19937_64 & rng);
	void ui_entities(sim::WorldPreset & preset);
	void ui_obstacles(sim::ObstaclePreset & preset, int & radio_index);
}