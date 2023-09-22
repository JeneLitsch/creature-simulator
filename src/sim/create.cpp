#include "create.hpp"

namespace sim {
	Ecs::Entity & create_entity(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = ecs.new_entity();
		entity.add(Transform{
			.location = {position},
			.rotation = {1,0},
		});
		grid[stx::vector2u{position}] = entity.get_id();
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
		entity.add(Barrier{});
		return entity;
	}



	Ecs::Entity & create_food(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = create_entity(ecs, position, grid);
		entity.add(Edible{ .value = 1.0f});
		entity.add(Sprite{
			.color = sf::Color::Green,
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
		entity.add(StomachSensorFB{entity.get_if<Transform>()});
		entity.add(StomachSensorLR{entity.get_if<Transform>()});
		entity.add(EdibleSensorFB{entity.get_if<Transform>()});
		entity.add(EdibleSensorLR{entity.get_if<Transform>()});
		entity.add(BarrierSensorFB{entity.get_if<Transform>()});
		entity.add(BarrierSensorLR{entity.get_if<Transform>()});
		entity.add(NeuralNetwork{14, 4});
		entity.add(Reproduction{config.reproduction.cooldown});
		return entity;
	}



	Ecs::Entity & create_barrier(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = create_entity(ecs, position, grid);
		entity.add(Sprite{
			.color = sf::Color{64,64,64}
		});
		entity.add(Barrier{});
		return entity;
	}
}