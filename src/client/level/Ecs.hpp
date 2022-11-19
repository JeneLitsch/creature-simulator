#pragma once
#include "shared/Ecs.hpp"
#include "client/level/Sprite.hpp"
#include "client/level/Position.hpp"

namespace client::level {
	using Ecs =	ecs::Ecs<
		Sprite,
		Position
	>;
}
