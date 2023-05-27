#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/read_sensors.hpp"
#include "senses/PheromoneSensor.hpp"
#include "senses/MetabolismSensor.hpp"

namespace server {
	constexpr std::uint64_t EMPTY = 0;
	constexpr std::uint64_t FIRST_CREATURE = 0xff;
	constexpr stx::size2u LEVEL_SIZE {256, 144};
	constexpr double spawn_chance = 0.01;



	Simulation::Simulation() 
		: grid{LEVEL_SIZE, EMPTY}
		, ecs{FIRST_CREATURE} {
		std::cout << "Server starting...\n";
		this->rng.seed(42);

		for(std::uint64_t x = 0; x < LEVEL_SIZE.x; ++x) {
			for(std::uint64_t y = 0; y < LEVEL_SIZE.y; ++y) {
				if(stx::flip(rng, spawn_chance)) {
					auto & entity = this->ecs.new_entity();
					this->grid(x,y) = entity.get_id();
				}
			}
		}
	}



	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		// HACK HACK HACK
		std::cout << "tick()";
	}



	const stx::grid2<std::uint64_t> & Simulation::get_grid() const {
		return this->grid;
	}



	const Ecs & Simulation::get_ecs() const {
		return this->ecs;
	}
}