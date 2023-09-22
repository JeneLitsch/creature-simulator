#pragma once
#include "nanocomp/nanocomp.hpp"
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
#include "sim/component/Barrier.hpp"

namespace sim {
	using StomachSensorFB = EntitySensor<Stomach, EntitySensorAxis::front_back>;
	using StomachSensorLR = EntitySensor<Stomach, EntitySensorAxis::left_right>;
	using EdibleSensorFB = EntitySensor<Edible, EntitySensorAxis::front_back>;
	using EdibleSensorLR = EntitySensor<Edible, EntitySensorAxis::left_right>;
	using BarrierSensorFB = EntitySensor<Barrier, EntitySensorAxis::front_back>;
	using BarrierSensorLR = EntitySensor<Barrier, EntitySensorAxis::left_right>;

	using Ecs =	nc::Ecs<
		Stomach, 
		Transform, 
		Movement, 
		Age, 
		Reproduction, 
		Edible, 
		FoodSpawn,
		Sprite, 
		Health,
		NeuralNetwork,
		Barrier,

		StomachSensorFB, 
		StomachSensorLR, 
		EdibleSensorFB, 
		EdibleSensorLR,
		BarrierSensorFB, 
		BarrierSensorLR
	>;

	struct EntitySensorConfig{
        double sensibility = 20.0;
		int radius = 25;
		bool enable_food_sensor = true;
		bool enable_stomach_sensor = true;
		bool enable_barrier_sensor = true;
    };

	struct MetabolismConfig{
		// Maximum food creatures can hold in their stomach
		double max_stomach = 10.0;
		// How much food always gets removed from the Stomach per tick
		double natural_food_decay_per_tick = 0.0005;
		// How much food is used when moving
		double food_decay_per_move = 0.0005;
		// How much Health gets removed per Tick while the Stomach is empty
		double starving_health_decay_per_tick = 0.02;
		// How much Health gets regenerated per Tick, when not starving
		double health_regen_per_tick = 0.05;
		// How much food gets used to regenerate Health (ratio)
		double food_per_health_regenerated = 1.0;
		// Should food sharing be enabled
		bool enable_food_sharing = true;
		// How much food can be given per tick per neighbour
		double food_shared = 0.005;
	};

	struct Config{
		uint16_t max_age = 1000;
		bool enable_short_oscilator = false;
		bool enable_long_oscilator = false;
		NeuralNetConfig neural_net = NeuralNetConfig{};
		ReproductionConfig reproduction = ReproductionConfig{};
		EntitySensorConfig sensors = EntitySensorConfig{};
		MetabolismConfig metabolism = MetabolismConfig{};
	};
}
