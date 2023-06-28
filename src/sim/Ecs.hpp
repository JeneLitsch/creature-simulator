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
#include "sim/component/FoodSpawn.hxx"
#include "sim/component/EntitySensor.hpp"

namespace sim {
	using StomachSensorFB = EntitySensor<Stomach, EntitySensorAxis::front_back>;
	using StomachSensorLR = EntitySensor<Stomach, EntitySensorAxis::left_right>;
	using EdibleSensorFB = EntitySensor<Edible, EntitySensorAxis::front_back>;
	using EdibleSensorLR = EntitySensor<Edible, EntitySensorAxis::left_right>;

	using Ecs =	nc::Ecs<
		PheromoneEmitter, 
		Sensors, 
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
		EdibleSensorLR
	>;

	struct EntitySensorConfig{
        double sensibility = 20.0;
    };

	struct Config{
		NeuralNetMutConfig neural_net = NeuralNetMutConfig{};
		ReproductionMutConfig reproduction = ReproductionMutConfig{};
		EntitySensorConfig creature_sensor = EntitySensorConfig{};
		EntitySensorConfig food_sensor = EntitySensorConfig{};
	};
}
