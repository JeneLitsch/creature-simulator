#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/move.hpp"
#include "system/reproduce.hpp"
#include "system/spawn_food.hpp"
#include "component/Movement.hpp"
#include "senses/PheromoneSensor.hpp"
#include "component/Age.hpp"
#include "disperse_pheromones.hpp"
#include "create.hpp"

namespace sim {
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
				} break;
				case 1: {
					// auto & entity = this->ecs.new_entity();
					// auto& transform = entity.add(Transform{
					// 	.location = {x, y}
					// });
					// entity.add(Sprite {
					// 	.color = sf::Color::Green,
					// });
					// entity.add(PheromoneEmitter{
					// 	.field = this->pheromone_field,
					// 	.composition = sf::Color{0,255,0},
					// 	.distance = 2,
					// });
					// entity.add(Age{});
					// entity.add(Edible{
					// 	.value = 0.1,
					// });
					// this->grid(x,y) = entity.get_id();
				} break;
				case 50: {
					create_food_spawner(ecs, {x,y}, grid);
				}
				default:break;
				}

			}
		}
	}



	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		ecs.run_system(move, ecs);
		ecs.run_system(metabolize);
		ecs.run_system([this](Ecs::Entity& entity) {
			if(Age* age = entity.get_if<Age>()) age -> incrementAge();
			if(Reproduction* reproduction = entity.get_if<Reproduction>()) reproduction -> incrementCooldown();
			reproduce(&(this -> grid), &(this -> ecs), &(this -> pheromone_field), entity, Config{});
		});
		this->pheromone_field.swap();
		ecs.run_system(emit_pheromones);
		ecs.run_system(spawn_food, this->grid, this->ecs, this->rng, this->pheromone_field);
		this->pheromone_field.display();
		this->ecs.clean_up();
	}



	stx::grid2<std::uint64_t> & Simulation::get_grid() {
		return this->grid;
	}


	
	const stx::grid2<std::uint64_t> & Simulation::get_grid() const {
		return this->grid;
	}



	PheromoneField & Simulation::get_pheromone_field() {
		return this->pheromone_field;
	}


	const PheromoneField & Simulation::get_pheromone_field() const {
		return this->pheromone_field;
	}



	Ecs & Simulation::get_ecs() {
		return this->ecs;
	}



	const Ecs & Simulation::get_ecs() const {
		return this->ecs;
	}
}