#pragma once
#include "shared/Ecs.hpp"
#include "server/Position.hpp"
#include "server/Rotation.hpp"

namespace server {
	using Ecs =	ecs::Ecs<
		Position,
		Rotation
	>;
}
