#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/read_sensors.hpp"
#include "system/move.hpp"
#include "senses/PheromoneSensor.hpp"
#include "system/reproduce.hpp"
#include "component/Movement.hpp"
#include "component/Age.hpp"
#include "disperse_pheromones.hpp"

namespace server {
	constexpr std::uint64_t EMPTY = 0;
	constexpr std::uint64_t FIRST_CREATURE = 256;
	constexpr stx::size2u LEVEL_SIZE {256, 144};
	constexpr double spawn_chance = 0.001;


	Simulation::Simulation() 
		: grid{LEVEL_SIZE, EMPTY}
		, pheromone_field{LEVEL_SIZE}
		, ecs{FIRST_CREATURE} {
		this->rng.seed(42);

		std::uniform_int_distribution<std::uint8_t> channel {0,64};
		std::uniform_int_distribution<int> type {0,1000};

		for(int x = 0; x < LEVEL_SIZE.x; ++x) {
			for(int y = 0; y < LEVEL_SIZE.y; ++y) {
				switch (type(rng)) {
				case 0: {
					auto & entity = this->ecs.new_entity();
					auto& transform = entity.add(Transform{
						.location = {x, y}
					});
					entity.add(Movement{&transform, &grid});
					entity.add(Age{});
					entity.add(Reproduction{5});
					entity.add(Stomach{
						.food = 1.0,
					});
					this->grid(x,y) = entity.get_id();
				} break;
				case 1: {
					auto & entity = this->ecs.new_entity();
					auto& transform = entity.add(Transform{
						.location = {x, y}
					});
					entity.add(Sprite {
						.color = sf::Color::Green,
					});
					entity.add(PheromoneEmitter{
						.field = this->pheromone_field,
						.composition = sf::Color{0,255,0},
						.distance = 2,
					});
					entity.add(Age{});
					entity.add(Edible{
						.value = 0.1,
					});
					this->grid(x,y) = entity.get_id();
				} break;
				default:break;
				}
			}
		}
	}



	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		ecs.run_system([&] (Ecs::Entity& entity) { move(entity, ecs); });
		ecs.run_system(metabolize);
		ecs.run_system([this](Ecs::Entity& entity) {
			if(Age* age = entity.get_if<Age>()) age -> incrementAge();
			if(Reproduction* reproduction = entity.get_if<Reproduction>()) reproduction -> incrementCooldown();
			reproduce(&(this -> grid), &(this -> ecs), &(this -> pheromone_field), entity, MutConfig{});
		});
		this->pheromone_field.swap();
		ecs.run_system(emit_pheromones);
		this->pheromone_field.display();
		this->ecs.clean_up();
	}



	const stx::grid2<std::uint64_t> & Simulation::get_grid() const {
		return this->grid;
	}



	const PheromoneField & Simulation::get_pheromone_field() const {
		return this->pheromone_field;
	}



	Ecs & Simulation::get_ecs() {
		return this->ecs;
	}
}