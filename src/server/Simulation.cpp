#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/read_sensors.hpp"
#include "senses/PheromoneSensor.hpp"
#include "senses/MetabolismSensor.hpp"
#include "component/Movement.hpp"
#include "component/Age.hpp"

namespace server {
	constexpr std::uint64_t EMPTY = 0;
	constexpr std::uint64_t FIRST_CREATURE = 256;
	constexpr stx::size2u LEVEL_SIZE {256, 144};
	constexpr double spawn_chance = 0.1;



	Simulation::Simulation() 
		: grid{LEVEL_SIZE, EMPTY}
		, ecs{FIRST_CREATURE} {
		this->rng.seed(42);

		for(std::uint64_t x = 0; x < LEVEL_SIZE.x; ++x) {
			for(std::uint64_t y = 0; y < LEVEL_SIZE.y; ++y) {
				if(stx::flip(rng, spawn_chance)) {
					auto & entity = this->ecs.new_entity();
					entity.add(Movement{
						.position = {static_cast<int>(x), static_cast<int>(y)},
						.direction = {0, 0},
						.grid = &grid});
					entity.add(Age{});
					this->grid(x,y) = entity.get_id();
				}
			}
		}
	}



	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		ecs.run_system([](Ecs::Entity& entity) {
			if(Movement* movement = entity.get_if<Movement>()) movement -> move();
			if(Age* age = entity.get_if<Age>()) age -> incrementAge();
		});
	}



	const stx::grid2<std::uint64_t> & Simulation::get_grid() const {
		return this->grid;
	}



	Ecs & Simulation::get_ecs() {
		return this->ecs;
	}
}