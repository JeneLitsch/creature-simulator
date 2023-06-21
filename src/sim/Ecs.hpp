#pragma once
#include "nanocomp/nanocomp.hpp"
#include "sim/component/PheromoneEmitter.hpp"
#include "sim/component/Sensors.hpp"
#include "sim/component/Stomach.hpp"
#include "sim/component/Transform.hpp"
#include "sim/component/Movement.hpp"
#include "sim/component/Age.hpp"
#include "sim/component/Reproduction.hpp"
#include "sim/component/NeuralNetwork.hpp"
#include "sim/component/Edible.hpp"
#include "sim/component/Sprite.hpp"

namespace sim {
	using Ecs =	nc::Ecs<PheromoneEmitter, Sensors, Stomach, Transform, Movement, Age, Reproduction, Edible, Sprite>;

	struct MutConfig{
		NeuralNetMutConfig neural_net = NeuralNetMutConfig{};
		ReproductionMutConfig reproduction = ReproductionMutConfig{};
	};
}
