#pragma once
#include <cstdint>
#include <variant>
#include "stdxx/vector.hxx"

namespace sim {


	struct ObstaclePreset {
		struct None {};
		
		struct Rocks {
			std::uint32_t cores = 0;
			std::uint32_t build_up = 0;
		};
		
		std::variant<
			None,
			Rocks
		> policy = None{}; 
	};


	struct WorldPreset {
		std::uint64_t seed = 42;
		stx::size2u32 size = {64,64};

		struct {
			std::uint32_t food_spawners = 5;
			std::uint32_t empty_creatures = 5;
		} entities;

		ObstaclePreset obstacles;
	};
}