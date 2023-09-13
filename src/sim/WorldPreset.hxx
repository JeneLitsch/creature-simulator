#pragma once
#include <cstdint>

namespace sim {
	struct WorldPreset {
		std::uint64_t seed = 42;
		std::uint64_t width = 64;
		std::uint64_t height = 64;
	};
}