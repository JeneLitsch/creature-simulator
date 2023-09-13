#pragma once
#include <cstdint>
#include "stdxx/vector.hxx"

namespace sim {

	struct WallGenRocks {

	};

	struct WorldPreset {
		std::uint64_t seed = 42;
		stx::size2u32 size = {16,16};

		std::uint64_t barriers = 5;

		struct {
			std::uint64_t food_spawners = 5;
			std::uint64_t empty_creatures = 5;
		} entities;
	};
}