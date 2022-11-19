#pragma once
#include "shared/Ecs.hpp"
#include "client/level/Position.hpp"
#include "client/level/Rotation.hpp"
#include "client/level/Sprite.hpp"

namespace client::level {
	using Ecs =	ecs::Ecs<
		Position,
		Rotation,
		Sprite
	>;
}
