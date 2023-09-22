#pragma once
#include "stdxx/vector.hxx"
#include "Ecs.hpp"

namespace sim {
	Ecs::Entity & create_entity(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid);
	Ecs::Entity & create_food_spawner(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid);
	Ecs::Entity & create_food(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid, const MetabolismConfig & config);
	Ecs::Entity & create_creature(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid, const Config& config, double initial_food_value);
	Ecs::Entity & create_barrier(Ecs & ecs, stx::vector2i position, stx::grid2<std::uint64_t> & grid);
}