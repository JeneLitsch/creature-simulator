#include "spawn_food.hpp"
#include "sim/create.hpp"

namespace sim {
	void spawn_food(Ecs::Entity & entity, stx::grid2<std::uint64_t> & grid, Ecs & ecs, Xoshiro::Xoshiro256PP & rng) {
		auto * food_spawn = entity.get_if<FoodSpawn>();
		auto * transform = entity.get_if<Transform>();
		if(!food_spawn) return;
		if(!transform) return;

		if(food_spawn->spawn_counter++ < food_spawn->spawn_cooldown) return;
		food_spawn->spawn_counter = 0;

		std::uniform_int_distribution<int> dist{
			-food_spawn->spawn_radius,
			+food_spawn->spawn_radius
		};

		stx::vector2i offset {dist(rng), dist(rng)};
		stx::vector2i food_position = transform->location + offset;

		if(grid.in_range(food_position) && grid[food_position] == 0) {
			create_food(ecs, food_position, grid);
		}
	}
}
