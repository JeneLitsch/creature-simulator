#pragma once
#include "nanocomp/nanocomp.hpp"
#include "server/component/PheromoneEmitter.hpp"
#include "server/component/Transform.hpp"
#include "server/component/Sensors.hpp"
#include "server/component/Metabolism.hpp"

namespace server {
	using Ecs =	nc::Ecs<
		Transform,
		Sensors,
		PheromoneEmitter,
		Metabolism
	>;
}
