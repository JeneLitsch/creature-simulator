#include "export.hxx"

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
			json["color"].push_back(comp.color.b);
			json["color"].push_back(comp.color.b);
		}	



		void export_comp(stx::json::write_iterator, const auto &) {}	



		template<typename Comp>
		void export_if(const Ecs::Entity & entity, stx::json::write_iterator json) {
			if(auto * comp = entity.get_if<Comp>()) {
				export_comp(json = stx::json::object, *comp);
			}
		}
	}
	


	stx::json::node export_entity(const Ecs::Entity & entity) {
		stx::json::node node;
		stx::json::write_iterator json{node};
		json = stx::json::object;

		json["id"] = entity.get_id();

		export_if<PheromoneEmitter>(entity, json["pheromone_wmitter"]);
		export_if<Stomach>(entity, json["stomach"]);
		export_if<Transform>(entity, json["transform"]);
		export_if<Movement>(entity, json["movement"]);
		export_if<Age>(entity, json["age"]);
		export_if<Reproduction>(entity, json["reproduction"]);
		export_if<Edible>(entity, json["edible"]);
		export_if<FoodSpawn>(entity, json["food_spawn"]);
		export_if<Sprite>(entity, json["sprite"]);

		// TODO: Sensors
	
		return node;
	}



	stx::json::node export_ecs(const Ecs & ecs) {
		stx::json::node node;
		stx::json::write_iterator json{node};
		stx::json::write_iterator entities = json["entities"] = stx::json::array;

		ecs.run_system([&] (const Ecs::Entity & entity) {
			entities.push_back(export_entity(entity));
		});

		return node;
	}
}