#include "create.hpp"

namespace sim {
	Ecs::Entity & create_entity(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = ecs.new_entity();
		auto & transform = entity.add(Transform{
			.location = {position},
			.rotation = {1,0},
		});
		grid[position] = entity.get_id();
		return entity;
	}



	Ecs::Entity & create_food_spawner(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = create_entity(ecs, position, grid);
		entity.add(FoodSpawn{
			.spawn_radius = 5,
			.spawn_cooldown = 100,
			.spawn_counter = 0,
		});
		entity.add(Sprite{
			.color = sf::Color::Red,
		});
		return entity;
	}



	Ecs::Entity & create_food(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid, PheromoneField & phero_field) {
		auto & entity = create_entity(ecs, position, grid);
		entity.add(Edible{ .value = 1.0f});
		entity.add(Sprite{
			.color = sf::Color::Green,
		});
		entity.add(PheromoneEmitter{
			.field = phero_field,
			.composition = sf::Color{0, 4, 0},
			.distance = 5,
		});
		return entity;
	}

	Ecs::Entity & create_creature(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid, const Config& config, double initial_food_value) {
		auto & entity = create_entity(ecs, position, grid);
		entity.add(Age{});
		entity.add(Stomach{ .food = initial_food_value});
		entity.add(Health{});
		entity.add(Sprite{});
		entity.add(Movement{entity.get_if<Transform>(), &grid});
		entity.add(StomachSensorFB{entity.get_if<Transform>(), config.creature_sensor.range});
		entity.add(StomachSensorLR{entity.get_if<Transform>(), config.creature_sensor.range});
		entity.add(EdibleSensorFB{entity.get_if<Transform>(), config.food_sensor.range});
		entity.add(EdibleSensorLR{entity.get_if<Transform>(), config.food_sensor.range});
		entity.add(NeuralNetwork{9, 4});
		entity.add(Reproduction{config.reproduction.default_cooldown});
		return entity;
	}
}