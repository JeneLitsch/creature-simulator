#pragma once
#include "nanocomp/nanocomp.hpp"
#include "client/level/Position.hpp"
#include "client/level/Rotation.hpp"
#include "client/level/Sprite.hpp"

namespace client::level {
	using Ecs =	nc::Ecs<
		Position,
		Rotation,
		Sprite
	>;
}
