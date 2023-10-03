#include "Simulation.hpp"
#include "stdxx/random.hxx"
#include <iostream>
#include <numbers>
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
#include "system/share_food.hpp"

namespace sim {
	constexpr std::uint64_t EMPTY = 0;
	constexpr std::uint64_t FIRST_CREATURE = 256;

	Simulation::Simulation(stx::size2u32 size) 
		: ecs{FIRST_CREATURE} 
		, grid{size, EMPTY} {
	}


	Simulation::~Simulation() {}

	
	
	void Simulation::tick() {
		tickCounter++;
		ecs.run_system(metabolize, this->config.metabolism);
		ecs.run_system([this](Ecs::Entity& entity) {
			if(Age* age = entity.get_if<Age>()) age -> increment_age();
			StomachSensorFB* sensor_1 = entity.get_if<StomachSensorFB>();
			StomachSensorLR* sensor_2 = entity.get_if<StomachSensorLR>();
			EdibleSensorFB* sensor_3 = entity.get_if<EdibleSensorFB>();
			EdibleSensorLR* sensor_4 = entity.get_if<EdibleSensorLR>();
			BarrierSensorFB* sensor_5 = entity.get_if<BarrierSensorFB>();
			BarrierSensorLR* sensor_6 = entity.get_if<BarrierSensorLR>();
			std::vector<Ecs::Entity*> neighbourhood;
			if((config.sensors.enable_stomach_sensor && (sensor_1 || sensor_2))
			|| (config.sensors.enable_food_sensor && (sensor_3 || sensor_4))
			|| (config.sensors.enable_barrier_sensor && (sensor_5 || sensor_6))){
				neighbourhood = visit_neighborhood(entity, grid, ecs, config.sensors);
			}
			if(config.sensors.enable_stomach_sensor && sensor_1) update_entity_sensor(sensor_1, neighbourhood, config.sensors);
			if(config.sensors.enable_stomach_sensor && sensor_2) update_entity_sensor(sensor_2, neighbourhood, config.sensors);
			if(config.sensors.enable_food_sensor && sensor_3) update_entity_sensor(sensor_3, neighbourhood, config.sensors);
			if(config.sensors.enable_food_sensor && sensor_4) update_entity_sensor(sensor_4, neighbourhood, config.sensors);
			if(config.sensors.enable_barrier_sensor && sensor_5) update_entity_sensor(sensor_5, neighbourhood, config.sensors);
			if(config.sensors.enable_barrier_sensor && sensor_6) update_entity_sensor(sensor_6, neighbourhood, config.sensors);
		});
		double oscilator_short = 0;
		if(config.enable_short_oscilator){
			oscilator_short = std::sin(static_cast<double>(tickCounter)/30.0*std::numbers::pi_v<double>);
		}
		double oscilator_long = 0;
		if(config.enable_long_oscilator){
			oscilator_long = std::sin(static_cast<double>(tickCounter)/600.0*std::numbers::pi_v<double>);
		}
		ecs.run_system(eval_neural, config, oscilator_short, oscilator_long);
		if(config.metabolism.enable_food_sharing){
			ecs.run_system(share_food, grid, &ecs, config);
		}
		ecs.run_system(move, ecs, *this, config.metabolism);
		ecs.run_system(reproduce, &(this -> grid), &(this -> ecs), this->config, this->rng);
		ecs.run_system(spawn_food, this->grid, this->ecs, this->rng, this->config.metabolism);
		ecs.run_system(check_death, *this, this->config);
		this->ecs.clean_up();
	}



	stx::grid2<std::uint64_t> & Simulation::get_grid() {
		return this->grid;
	}


	
	const stx::grid2<std::uint64_t> & Simulation::get_grid() const {
		return this->grid;
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