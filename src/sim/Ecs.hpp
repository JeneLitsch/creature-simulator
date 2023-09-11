#pragma once
#include "nanocomp/nanocomp.hpp"
#include "sim/component/PheromoneEmitter.hpp"
#include "sim/component/Stomach.hpp"
#include "sim/component/Transform.hpp"
#include "sim/component/Movement.hpp"
#include "sim/component/Age.hpp"
#include "sim/component/Reproduction.hpp"
#include "sim/component/NeuralNetwork.hpp"
#include "sim/component/Edible.hpp"
#include "sim/component/Sprite.hpp"
#include "sim/component/FoodSpawn.hpp"
#include "sim/component/EntitySensor.hpp"
#include "sim/component/Health.hpp"

namespace sim {
	using StomachSensorFB = EntitySensor<Stomach, EntitySensorAxis::front_back>;
	using StomachSensorLR = EntitySensor<Stomach, EntitySensorAxis::left_right>;
	using EdibleSensorFB = EntitySensor<Edible, EntitySensorAxis::front_back>;
	using EdibleSensorLR = EntitySensor<Edible, EntitySensorAxis::left_right>;

	using Ecs =	nc::Ecs<
		PheromoneEmitter, 
		Stomach, 
		Transform, 
		Movement, 
		Age, 
		Reproduction, 
		Edible, 
		FoodSpawn,
		Sprite, 
		StomachSensorFB, 
		StomachSensorLR, 
		EdibleSensorFB, 
		EdibleSensorLR,
		Health
	>;

	struct EntitySensorConfig{
        double sensibility = 20.0;
    };

	struct MetabolismConfig{
		// How much food always gets removed from the Stomach per tick
		double naturalfoodDecayPerTick = 0.01;
		// How much Health gets removed per Tick while the Stomach is empty
		double starvingHealthDecayPerTick = 0.02;
		// How much Health gets regenerated per Tick, when not starving
		double healthRegenPerTick = 0.01;
		// How much food gets used to regenerate Health
		double foodPerHealthRegenerated = 1.0;
	};

	struct Config{
		uint16_t maxAge = 300;
		NeuralNetMutConfig neural_net = NeuralNetMutConfig{};
		ReproductionConfig reproduction = ReproductionConfig{};
		EntitySensorConfig creature_sensor = EntitySensorConfig{};
		EntitySensorConfig food_sensor = EntitySensorConfig{};
		MetabolismConfig metabolism = MetabolismConfig{};
	};
}
