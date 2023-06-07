#pragma once
#include "nanocomp/nanocomp.hpp"
#include "server/component/PheromoneEmitter.hpp"
#include "server/component/Sensors.hpp"
#include "server/component/Metabolism.hpp"
#include "server/component/Transform.hpp"
#include "server/component/Movement.hpp"
#include "server/component/Age.hpp"
#include "server/component/Edible.hpp"
#include "server/component/Sprite.hpp"

namespace server {
	using Ecs =	nc::Ecs<PheromoneEmitter, Sensors, Metabolism, Transform, Movement, Age, Edible, Sprite>;
}
