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
#include "sim/component/FoodSpawn.hxx"
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
		Health,
		NeuralNetwork
	>;

	struct EntitySensorConfig{
        double sensibility = 20.0;
		int range = 25;
    };

	struct MetabolismConfig{
		// Maximum food creatures can hold in their stomach
		double maxStomach = 5.0;
		// How much food always gets removed from the Stomach per tick
		double naturalfoodDecayPerTick = 0.001;
		// How much food is used when moving
		double foodDecayPerMove = 0.0005;
		// How much Health gets removed per Tick while the Stomach is empty
		double starvingHealthDecayPerTick = 0.02;
		// How much Health gets regenerated per Tick, when not starving
		double healthRegenPerTick = 0.05;
		// How much food gets used to regenerate Health (ratio)
		double foodPerHealthRegenerated = 1.0;
	};

	struct Config{
		uint16_t maxAge = 1000;
		NeuralNetMutConfig neural_net = NeuralNetMutConfig{};
		ReproductionConfig reproduction = ReproductionConfig{};
		EntitySensorConfig creature_sensor = EntitySensorConfig{};
		EntitySensorConfig food_sensor = EntitySensorConfig{};
		MetabolismConfig metabolism = MetabolismConfig{};
	};
}
