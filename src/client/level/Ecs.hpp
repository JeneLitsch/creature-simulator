#pragma once
#include "nanocomp/nanocomp.hpp"
#include "client/level/Transform.hpp"
#include "client/level/Sprite.hpp"

namespace client::level {
	using Ecs =	nc::Ecs<
		Transform,
		Sprite
	>;
}
