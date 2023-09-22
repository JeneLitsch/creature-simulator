#pragma once
#include "SFML/Graphics.hpp"
#include "Reproduction.hpp"
#include "xoshiro256.h"

namespace sim {
	struct Sprite {
		sf::Color color = {196, 196, 196};

		Sprite create_child(std::uint64_t seed, const ReproductionConfig & config, double mutation_dampener);
	};
}
