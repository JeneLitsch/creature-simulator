#include "import.hpp"
#include "Simulation.hpp"

namespace sim {
	namespace {
		stx::vector2i import_vector2i(stx::json::iterator json) {
			auto x = json[0].i32();
			auto y = json[1].i32();
			if(!x) throw stx::json::format_error {"Cannot read stx::vector2i::x"};
			if(!y) throw stx::json::format_error {"Cannot read stx::vector2i::y"};
			return stx::vector2i { *x, *y };
		}



		sf::Color import_color(stx::json::iterator json) {
			auto r = json[0].u8();
			auto g = json[1].u8();
			auto b = json[2].u8();
			if(!r) throw stx::json::format_error {"Cannot read sf::Color::r"};
			if(!g) throw stx::json::format_error {"Cannot read sf::Color::g"};
			if(!b) throw stx::json::format_error {"Cannot read sf::Color::b"};
			return sf::Color { *r, *g , *b };
		}



		PheromoneEmitter import_phero_emitter(stx::json::iterator json, stx::reference<PheromoneField> field) {
			auto distance = json["distance"].i32();
			if(!distance) throw stx::json::format_error {"Cannot read PheromoneEmitter::distance"};
			return PheromoneEmitter {
				.composition = import_color(json["composition"]),
				.distance = *distance,
				.field = field,
			};
		}



		Stomach import_stomach(stx::json::iterator json) {
			auto food = json["value"].number();
			if(!food) throw stx::json::format_error { "Cannot read Stomach::food" };
			return Stomach {
				.food = *food,
			};
		}



		Transform import_transform(stx::json::iterator json) {
			return Transform {
				.location = import_vector2i(json["location"]), 
				.rotation = import_vector2i(json["rotation"]),
			};
		}

		

		Movement import_movement(
			stx::json::iterator,
			Ecs::Entity & entity,
			stx::reference<stx::grid2<std::uint64_t>> grid) {
			
			auto * transform = entity.get_if<Transform>();
			if(!transform) throw stx::json::format_error { "Cannot add Movement without Transform" };
			return Movement{ transform, &*grid };
		}



		Age import_age(stx::json::iterator json) {
			auto age = json["distance"].u64();
			if(!age) throw stx::json::format_error { "Cannot read Age::age" };
			return Age {
				.age = *age,
			};
		}



		Reproduction import_reproduction(stx::json::iterator json) {
			auto current_cooldown = json["current_cooldown"].u64();
			auto max_cooldown = json["max_cooldown"].u64();
			auto wants_to_reproduce = json["wants_to_reproduce"].boolean();

			if(!current_cooldown) throw stx::json::format_error { "Cannot read Reproduction::current_cooldown" };
			if(!max_cooldown) throw stx::json::format_error { "Cannot read Reproduction::max_cooldown" };
			if(!wants_to_reproduce) throw stx::json::format_error { "Cannot read Reproduction::wants_to_reproduce" };
			
			return Reproduction { *current_cooldown, *max_cooldown, *wants_to_reproduce };
		}




		Edible import_edible(stx::json::iterator json) {
			auto value = json["value"].number();
			if(!value) throw stx::json::format_error { "Cannot read Edible::value" };
			return Edible {
				.value = *value,
			};
		}



		FoodSpawn import_food_spawn(stx::json::iterator json) {
			auto spawn_cooldown = json["spawn_cooldown"].i32();
			auto spawn_counter = json["spawn_counter"].i32();
			auto spawn_radius = json["spawn_radius"].i32();

			if(!spawn_cooldown) throw stx::json::format_error { "Cannot read FoodSpawn::spawn_cooldown" };
			if(!spawn_counter) throw stx::json::format_error { "Cannot read FoodSpawn::spawn_counter" };
			if(!spawn_radius) throw stx::json::format_error { "Cannot read FoodSpawn::spawn_radius" };
		
			return FoodSpawn {
				.spawn_cooldown = *spawn_cooldown,
				.spawn_counter = *spawn_counter,
				.spawn_radius = *spawn_radius,
			};
		}



		Sprite import_sprite(stx::json::iterator json) {
			return Sprite {
				.color = import_color(json["color"]),
			};
		}



		void import_if(Ecs::Entity & entity, auto json, auto import, auto && ...args) {
			if(json) {
				entity.add(import(json, args...));
			}
		}



		void import_entity(stx::json::iterator json, Simulation & sim, std::optional<std::uint64_t> override_id = std::nullopt) {
			auto & ecs = sim.get_ecs();
			auto & grid = sim.get_grid();
			auto & phero_field = sim.get_pheromone_field();

			auto & entity = override_id ? ecs.new_entity(*override_id) : ecs.new_entity();

			import_if(entity, json["pheromone_emitter"], import_phero_emitter, phero_field);
			import_if(entity, json["transform"], import_transform);
			import_if(entity, json["stomach"], import_stomach);
			import_if(entity, json["movement"], import_movement, entity, grid);
			import_if(entity, json["age"], import_age);
			import_if(entity, json["reproduction"], import_reproduction);
			import_if(entity, json["edible"], import_edible);
			import_if(entity, json["food_spawn"], import_food_spawn);
			import_if(entity, json["sprite"], import_sprite);
		};
	}



	void import_entity(stx::json::iterator json, Simulation & sim) {
		import_entity(json, sim, std::nullopt);
	};



	std::unique_ptr<Simulation> import_simulation(stx::json::iterator json) {
		auto sim = std::make_unique<Simulation>();
		for(const auto entity : stx::json::to_array(json["entities"])) {
			auto id = entity["id"].u64();
			if(!id) throw stx::json::format_error {"Cannot read entity id"};
			import_entity(entity["entity"], *sim, id);
		}
	}
}