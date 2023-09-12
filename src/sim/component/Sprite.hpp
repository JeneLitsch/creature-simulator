#pragma once
#include "SFML/Graphics.hpp"
#include "Reproduction.hpp"

namespace sim {
	struct Sprite {
		sf::Color color = {196, 196, 196};

		Sprite createChild(std::uint64_t seed, const ReproductionConfig & config, double mutationDampener){
			std::mt19937_64 rng;
		    rng.seed(seed);
			Sprite child = *this;
			std::uniform_int_distribution interval { -config.max_color_difference, config.max_color_difference };
			int difference = interval(rng);
            difference = difference - mutationDampener * difference;
			int new_value = child.color.r + difference;
			child.color.r = std::clamp(new_value, 128, UINT8_MAX);
			difference = interval(rng);
            difference = difference - mutationDampener * difference;
			new_value = child.color.g + difference;
			child.color.g = std::clamp(new_value, 128, UINT8_MAX);
			difference = interval(rng);
            difference = difference - mutationDampener * difference;
			new_value = child.color.b + difference;
			child.color.b = std::clamp(new_value, 128, UINT8_MAX);
            return child;
		}
	};
}