#pragma once
#include "stdxx/grid.hxx"

namespace sim {
	struct FoodSpawn {
		int spawn_radius = 0;
		int spawn_cooldown = 1;
		int spawn_counter = 0;
	};
}