#include "export.hpp"
#include "Simulation.hpp"
#include "shared/hex.hpp"

namespace sim {
	namespace {
		void export_comp(stx::json::write_iterator json, const PheromoneEmitter & comp) {
			json["composition"].push_back(comp.composition.r);
			json["composition"].push_back(comp.composition.g);
			json["composition"].push_back(comp.composition.b);
			json["distance"] = comp.distance;
		}

		
		
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




		template<typename SensedComp, EntitySensorAxis axis>
		void export_comp(stx::json::write_iterator json, const EntitySensor<SensedComp, axis> & comp) {
			json["radius"] = comp.radius;
			json["value"] = comp.value;
		}


		namespace {
		}



		void export_comp(stx::json::write_iterator json, const NeuralNetwork & comp) {
			json["input_size"] = comp.input_size;
			json["hidden_size"] = comp.hidden_size;
			json["output_size"] = comp.output_size;

			auto json_input_matrix = json["input_matrix"];
			json_input_matrix = stx::json::array;
			for(const auto & line : comp.inputMatrix) {
				stx::json::node node;
				stx::json::write_iterator json_line = node;
				for(const auto & elem : line) {
					json_line.push_back(elem);
				}
				json_input_matrix.push_back(node);
			}


			auto json_output_matrix = json["output_matrix"];
			json_output_matrix = stx::json::array;
			for(const auto & line : comp.outputMatrix) {
				stx::json::node node;
				stx::json::write_iterator json_line = node;
				for(const auto & elem : line) {
					json_line.push_back(elem);
				}
				json_output_matrix.push_back(node);
			}
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
		
		export_if<PheromoneEmitter>(entity, json, "pheromone_emitter");
		export_if<Stomach>(entity, json, "stomach");
		export_if<Transform>(entity, json, "transform");
		export_if<Movement>(entity, json, "movement");
		export_if<Age>(entity, json, "age");
		export_if<Reproduction>(entity, json, "reproduction");
		export_if<Edible>(entity, json, "edible");
		export_if<FoodSpawn>(entity, json, "food_spawn");
		export_if<Sprite>(entity, json, "sprite");
		export_if<NeuralNetwork>(entity, json, "neural_network");

		export_if<StomachSensorFB>(entity, json, "stomach_sensor_fb");
		export_if<StomachSensorLR>(entity, json, "stomach_sensor_lr");
		export_if<EdibleSensorFB>(entity, json, "edible_sensor_fb");
		export_if<EdibleSensorLR>(entity, json, "edible_sensor_lr");
	
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



		stx::json::node export_pheromone_field(const PheromoneField & field) {
			stx::json::node node;
			stx::json::write_iterator json{node};
			auto image = field.get_texture().copyToImage();
			auto begin = image.getPixelsPtr();
			auto size = (image.getSize().x * image.getSize().y) * 4;
			json = hex::encode(begin, size);
			return node;
		}
	}



	stx::json::node export_sim(const Simulation & sim) {
		stx::json::node node;
		stx::json::write_iterator json{node};
		json["entities"] = export_ecs(sim.get_ecs());
		json["pheromones"] = export_pheromone_field(sim.get_pheromone_field());
		json["tick_counter"] = sim.tickCounter;
		return node;
	}
}