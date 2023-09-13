#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/move.hpp"
#include "system/reproduce.hpp"
#include "system/spawn_food.hpp"
#include "component/Movement.hpp"
#include "component/Age.hpp"
#include "system/check_death.hpp"
#include "system/eval_neural_net.hpp"
#include "system/update_sensors.hpp"
#include "generate.hpp"

namespace sim {
	constexpr std::uint64_t EMPTY = 0;
	constexpr std::uint64_t FIRST_CREATURE = 256;
	constexpr double spawn_chance = 0.001;


	Simulation::Simulation(stx::size2u32 size) 
		: grid{size, EMPTY}
		, pheromone_field{size}
		, ecs{FIRST_CREATURE} {

	}



	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		ecs.run_system(metabolize, this->config.metabolism);
		ecs.run_system([this](Ecs::Entity& entity) {
			if(Age* age = entity.get_if<Age>()) age -> incrementAge();
			if(StomachSensorFB* sensor = entity.get_if<StomachSensorFB>()) update_entity_sensor(grid, ecs, sensor, config.creature_sensor);
			if(StomachSensorLR* sensor = entity.get_if<StomachSensorLR>()) update_entity_sensor(grid, ecs, sensor, config.creature_sensor);
			if(EdibleSensorFB* sensor = entity.get_if<EdibleSensorFB>()) update_entity_sensor(grid, ecs, sensor, config.food_sensor);
			if(EdibleSensorLR* sensor = entity.get_if<EdibleSensorLR>()) update_entity_sensor(grid, ecs, sensor, config.food_sensor);
		});
		ecs.run_system(eval_neural, config);
		ecs.run_system(move, ecs, *this, config.metabolism);
		ecs.run_system(reproduce, &(this -> grid), &(this -> ecs), &(this -> pheromone_field), this->config, this->rng);
		this->pheromone_field.swap();
		ecs.run_system(emit_pheromones);
		ecs.run_system(spawn_food, this->grid, this->ecs, this->rng, this->pheromone_field);
		ecs.run_system(check_death, *this, this->config);
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


	
	void Simulation::kill_entity(Ecs::Entity& entity){
		Transform & transform = entity.get<Transform>();
		this->grid[transform.location] = 0;
		entity.mark_delete();
	}



	std::unique_ptr<Simulation> Simulation::generate(const WorldPreset & preset) {
		return sim::generate(preset);
	}



	std::unique_ptr<Simulation> Simulation::empty(stx::size2u32 size) {
		return std::unique_ptr<Simulation>{new Simulation{size}};
	}
}