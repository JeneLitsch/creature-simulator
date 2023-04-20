#pragma once
#include "nanocomp/nanocomp.hpp"
#include "server/Position.hpp"
#include "server/Rotation.hpp"

namespace server {
	using Ecs =	nc::Ecs<
		Position,
		Rotation
	>;
}
