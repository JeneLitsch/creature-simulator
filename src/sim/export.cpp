#include "export.hpp"
#include "Simulation.hpp"
#include <iomanip>

namespace sim {
	namespace {
		void export_comp(stx::json::write_iterator json, const Stomach & comp) {
			json["food"] = comp.food;
		}



		void export_comp(stx::json::write_iterator json, const Transform & comp) {
			json["location"].push_back(comp.location.x);
			json["location"].push_back(comp.location.y);
			json["rotation"].push_back(comp.rotation.x);
			json["rotation"].push_back(comp.rotation.y);
		}	



		void export_comp(stx::json::write_iterator json, const Movement & comp) {
			json["direction"].push_back(comp.direction.x);
			json["direction"].push_back(comp.direction.y);
		}	



		void export_comp(stx::json::write_iterator json, const Age & comp) {
			json["age"] = comp.age;
		}	



		void export_comp(stx::json::write_iterator json, const Reproduction & comp) {
			json["current_cooldown"] = comp.current_cooldown;
			json["max_cooldown"] = comp.max_cooldown;
			json["wants_to_reproduce"] = comp.wants_to_reproduce;
		}



		void export_comp(stx::json::write_iterator json, const Edible & comp) {
			json["value"] = comp.value;
		}	



		void export_comp(stx::json::write_iterator json, const FoodSpawn & comp) {
			json["spawn_cooldown"] = comp.spawn_cooldown;
			json["spawn_counter"] = comp.spawn_counter;
			json["spawn_radius"] = comp.spawn_radius;
		}	



		void export_comp(stx::json::write_iterator json, const Sprite & comp) {
			json["color"].push_back(comp.color.r);
			json["color"].push_back(comp.color.g);
			json["color"].push_back(comp.color.b);
		}



		void export_comp(stx::json::write_iterator json, const Health & comp) {
			json["current_health"] = comp.current_health;
		}



		void export_comp(stx::json::write_iterator json, const Barrier &) {

		}



		template<typename SensedComp, EntitySensorAxis axis>
		void export_comp(stx::json::write_iterator json, const EntitySensor<SensedComp, axis> & comp) {
			json["value"] = comp.value;
		}


		namespace {
			stx::json::node export_matrix(const std::vector<std::vector<double>> & matrix) {
				stx::json::node node;
				stx::json::write_iterator json{node};
				json = stx::json::array;
				for(const auto & line : matrix) {
					stx::json::node node;
					stx::json::write_iterator json_line = node;
					for(const auto & elem : line) {
						json_line.push_back(elem);
					}
					json.push_back(node);
				}

				return node;
			}
		}



		void export_comp(stx::json::write_iterator json, const NeuralNetwork & comp) {
			json["input_size"] = comp.input_size;
			json["hidden_size"] = comp.hidden_size;
			json["output_size"] = comp.output_size;

			json["input_matrix"] = export_matrix(comp.input_matrix);
			json["hidden_matrix"] = export_matrix(comp.hidden_matrix);
			json["output_matrix"] = export_matrix(comp.output_matrix);
		}


		template<typename Comp>
		void export_if(const Ecs::Entity & entity, stx::json::write_iterator json, const std::string & name) {
			if(auto * comp = entity.get_if<Comp>()) {
				auto json_comp = json[name];
				export_comp(json_comp = stx::json::object, *comp);
			}
		}
	}
	


	stx::json::node export_entity(const Ecs::Entity & entity) {
		stx::json::node node;
		stx::json::write_iterator json{node};
		json = stx::json::object;
		
		export_if<Stomach>(entity, json, "stomach");
		export_if<Transform>(entity, json, "transform");
		export_if<Movement>(entity, json, "movement");
		export_if<Age>(entity, json, "age");
		export_if<Reproduction>(entity, json, "reproduction");
		export_if<Edible>(entity, json, "edible");
		export_if<FoodSpawn>(entity, json, "food_spawn");
		export_if<Sprite>(entity, json, "sprite");
		export_if<Health>(entity, json, "health");
		export_if<NeuralNetwork>(entity, json, "neural_network");
		export_if<Barrier>(entity, json, "barrier");

		export_if<StomachSensorFB>(entity, json, "stomach_sensor_fb");
		export_if<StomachSensorLR>(entity, json, "stomach_sensor_lr");
		export_if<EdibleSensorFB>(entity, json, "edible_sensor_fb");
		export_if<EdibleSensorLR>(entity, json, "edible_sensor_lr");
		export_if<BarrierSensorFB>(entity, json, "barrier_sensor_fb");
		export_if<BarrierSensorLR>(entity, json, "barrier_sensor_lr");
		

		return node;
	}



	namespace {
		stx::json::node export_ecs(const Ecs & ecs) {
			stx::json::node node;
			stx::json::write_iterator json{node};
			json = stx::json::array;

			ecs.run_system([&] (const Ecs::Entity & entity) {
				stx::json::node entity_node;
				stx::json::write_iterator entity_json{entity_node};
				entity_json["id"] = entity.get_id();
				entity_json["entity"] = export_entity(entity);
				json.push_back(entity_node);
			});

			return node;
		}



		stx::json::node export_rng(const Xoshiro::Xoshiro256PP & rng) {
			stx::json::node node;
			stx::json::write_iterator json{node};
			for(std::uint64_t state : rng.state) {
				// std::cout << "OUT: " << state  << "\n";
				std::ostringstream oss;
				oss << std::hex << std::setw(16) << std::setfill('0') << state;
				json.push_back(oss.str());
			}

			return node;
		}
	}



	stx::json::node export_sim(const Simulation & sim) {
		stx::json::node node;
		stx::json::write_iterator json{node};
		json["entities"] = export_ecs(sim.get_ecs());
		json["rng"] = export_rng(sim.rng);

		json["size"].push_back(sim.get_grid().size().x);
		json["size"].push_back(sim.get_grid().size().y);

		json["tick_counter"] = sim.tickCounter;
		return node;
	}
}