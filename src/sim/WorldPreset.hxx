#pragma once
#include <cstdint>
#include "stdxx/vector.hxx"

namespace sim {
	struct WorldPreset {
		std::uint64_t seed = 42;
		stx::size2u32 size = {16,16};
	};
}