#pragma once
#include "server/Ecs.hpp"

namespace server {
	void read_sensors(Ecs::Entity & entity, stx::position2i position);
}