#pragma once
#include "nanocomp/nanocomp.hpp"
#include "server/component/PheromoneEmitter.hpp"
#include "server/component/Sensors.hpp"
#include "server/component/Metabolism.hpp"
#include "server/component/Transform.hpp"
#include "server/component/Movement.hpp"
#include "server/component/Age.hpp"
#include "server/component/Reproduction.hpp"
#include "server/component/NeuralNetwork.hpp"

namespace server {
	using Ecs =	nc::Ecs<PheromoneEmitter, Sensors, Metabolism, Transform, Movement, Age, Reproduction>;

	struct MutConfig{
		NeuralNetMutConfig neural_net = NeuralNetMutConfig{};
		ReproductionMutConfig reproduction = ReproductionMutConfig{};
	};
}
