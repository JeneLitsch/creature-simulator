#pragma once
#include "nanocomp/nanocomp.hpp"
#include "server/component/PheromoneEmitter.hpp"
#include "server/component/Position.hpp"
#include "server/component/Rotation.hpp"
#include "server/component/Sensors.hpp"
#include "server/component/Metabolism.hpp"

namespace server {
	using Ecs =	nc::Ecs<
		Position,
		Rotation,
		Sensors,
		PheromoneEmitter,
		Metabolism
	>;
}
