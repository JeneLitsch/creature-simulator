#include "create.hpp"

namespace sim {
	Ecs::Entity & create_entity(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid) {
		auto & entity = ecs.new_entity();
		auto & transform = entity.add(Transform{
			.location = {position},
			.rotation = {0,0},
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
		entity.add(Edible{ .value = 0.1f});
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
}