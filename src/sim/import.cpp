#include "import.hpp"
#include "Simulation.hpp"
#include "stdxx/log.hxx"

namespace sim {
	namespace {
		stx::vector2u32 import_vector2u32(stx::json::iterator json) {
			auto x = json[0].u32();
			auto y = json[1].u32();
			if(!x) throw stx::json::format_error {"Cannot read stx::vector2u32::x"};
			if(!y) throw stx::json::format_error {"Cannot read stx::vector2u32::y"};
			return stx::vector2u32 { *x, *y };
		}

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



		Stomach import_stomach(stx::json::iterator json) {
			auto food = json["food"].number();
			if(!food) throw stx::json::format_error { "Cannot read Stomach::food" };
			return Stomach {
				.food = *food,
			};
		}



		Transform import_transform(
			stx::json::iterator json,
			Ecs::Entity & entity,
			stx::reference<stx::grid2<std::uint64_t>> grid) {
			
			auto location = import_vector2i(json["location"]);
			auto rotation = import_vector2i(json["rotation"]);

			(*grid)[location] = entity.get_id();

			return Transform {
				.location = location, 
				.rotation = rotation,
			};
		}

		

		Movement import_movement(
			stx::json::iterator json,
			Ecs::Entity & entity,
			stx::reference<stx::grid2<std::uint64_t>> grid) {
			
			auto * transform = entity.get_if<Transform>();
			if(!transform) throw stx::json::format_error { "Cannot add Movement without Transform" };
			auto movement = Movement{ transform, &*grid };
			movement.direction = import_vector2i(json["direction"]);
			return movement;
		}



		Age import_age(stx::json::iterator json) {
			auto age = json["age"].u64();
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
			
			return Reproduction { *max_cooldown, *current_cooldown, *wants_to_reproduce };
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
				.spawn_radius = *spawn_radius,
				.spawn_cooldown = *spawn_cooldown,
				.spawn_counter = *spawn_counter,
			};
		}



		Sprite import_sprite(stx::json::iterator json) {
			return Sprite {
				.color = import_color(json["color"]),
			};
		}



		Health import_health(stx::json::iterator json) {
			auto current_health = json["current_health"].number();
			if(!current_health) throw stx::json::format_error { "Cannot read Health::current_health" };
			return Health {
				.current_health = *current_health,
			};
		}



		Barrier import_barrier(stx::json::iterator json) {
			return Barrier {};
		}



		template<typename Sensor>
		Sensor import_entity_sensor(
			stx::json::iterator json,
			Ecs::Entity & entity) {

			auto * transform = entity.get_if<Transform>();
			if(!transform) throw stx::json::format_error { "Cannot add Movement without Transform" };

			auto value = json["value"].number();
			if(!value) throw stx::json::format_error { "Cannot read EntitySensor<...>::value" };

			auto sensor = Sensor { transform };
			sensor.value = *value;

			return sensor;
		}



		namespace {
			std::vector<std::vector<double>> import_matrix(stx::json::iterator json) {
				std::vector<std::vector<double>> matrix;
				for(const auto & line : stx::json::to_array(json)) {
					matrix.push_back({});
					for(const auto & elem : stx::json::to_array(line)) {
						auto num = elem.force_number();
						matrix.back().push_back(num);
					}
				}
				return matrix;
			}
		}



		NeuralNetwork import_neural_network(stx::json::iterator json) {
			NeuralNetwork neural_network{0,0};
			const auto input_size = json["input_size"].u64();
			const auto hidden_size = json["hidden_size"].u64();
			const auto output_size = json["output_size"].u64();

			if(!input_size) throw stx::json::format_error{"Cannot import NeuralNetwork::input_size"};
			if(!hidden_size) throw stx::json::format_error{"Cannot import NeuralNetwork::hidden_size"};
			if(!output_size) throw stx::json::format_error{"Cannot import NeuralNetwork::output_size"};
			
			neural_network.input_size = *input_size; 
			neural_network.hidden_size = *hidden_size; 
			neural_network.output_size = *output_size;

			neural_network.input_matrix = import_matrix(json["input_matrix"]);
			neural_network.hidden_matrix = import_matrix(json["hidden_matrix"]);
			neural_network.output_matrix = import_matrix(json["output_matrix"]);
			
			return neural_network;
		}



		void import_if(Ecs::Entity & entity, auto json, auto import, auto && ...args) {
			if(json && !json.null()) {
				entity.add(import(json, args...));
			}
		}



		void import_entity(stx::json::iterator json, Simulation & sim, std::optional<std::uint64_t> override_id = std::nullopt) {
			auto & ecs = sim.get_ecs();
			auto & grid = sim.get_grid();

			auto & entity = override_id ? ecs.new_entity(*override_id) : ecs.new_entity();

			import_if(entity, json["transform"], import_transform, entity, grid);
			import_if(entity, json["stomach"], import_stomach);
			import_if(entity, json["movement"], import_movement, entity, grid);
			import_if(entity, json["age"], import_age);
			import_if(entity, json["reproduction"], import_reproduction);
			import_if(entity, json["edible"], import_edible);
			import_if(entity, json["food_spawn"], import_food_spawn);
			import_if(entity, json["sprite"], import_sprite);
			import_if(entity, json["neural_network"], import_neural_network);
			import_if(entity, json["health"], import_health);
			import_if(entity, json["barrier"], import_barrier);

			import_if(entity, json["stomach_sensor_fb"], import_entity_sensor<StomachSensorFB>, entity);
			import_if(entity, json["stomach_sensor_lr"], import_entity_sensor<StomachSensorLR>, entity);
			import_if(entity, json["edible_sensor_fb"], import_entity_sensor<EdibleSensorFB>, entity);
			import_if(entity, json["edible_sensor_lr"], import_entity_sensor<EdibleSensorLR>, entity);
			import_if(entity, json["barrier_sensor_fb"], import_entity_sensor<BarrierSensorFB>, entity);
			import_if(entity, json["barrier_sensor_lr"], import_entity_sensor<BarrierSensorLR>, entity);
			
		};



		void import_rng(stx::json::iterator json, Xoshiro::Xoshiro256PP & rng) {
			auto state = stx::json::to_array(json);
			for(std::size_t i = 0; i < std::min<std::size_t>(4, std::size(state)); ++i) {
				if(auto str = state[i].string()) {
					std::istringstream iss {*str};
					iss >> std::hex >> rng.state[i];
					// std::cout << "IN: " << rng.state[i] << "\n";
				}
			}
		}
	}



	void import_entity(stx::json::iterator json, Simulation & sim) {
		import_entity(json, sim, std::nullopt);
	};



	std::unique_ptr<Simulation> import_simulation(stx::json::iterator json) {
		auto size = stx::size2u32{import_vector2u32(json["size"])};
		auto sim = Simulation::empty(size);
		sim->tickCounter = json["tick_counter"].u64().value_or(0);
		import_rng(json["rng"], sim->rng);
		for(const auto entity : stx::json::to_array(json["entities"])) {
			auto id = entity["id"].u64();
			if(!id) throw stx::json::format_error {"Cannot read entity id"};
			import_entity(entity["entity"], *sim, id);
		}
		return sim;
	}
}