#pragma once
#include "SFML/Graphics.hpp"
#include "Reproduction.hpp"
#include "shared/random/xoshiro256.h"

namespace sim {
	struct Sprite {
		sf::Color color = {196, 196, 196};

		Sprite createChild(std::uint64_t seed, const ReproductionConfig & config, double mutationDampener){
            Xoshiro::Xoshiro256PP rng;
		    rng.seed(seed);
			Sprite child = *this;
			std::uniform_int_distribution interval { -config.max_color_difference, config.max_color_difference };
			int difference = interval(rng);
            difference = difference - mutationDampener * difference;
			int new_value = child.color.r + difference;
			child.color.r = std::clamp(new_value, 0, UINT8_MAX);
			difference = interval(rng);
            difference = difference - mutationDampener * difference;
			new_value = child.color.g + difference;
			child.color.g = std::clamp(new_value, 0, UINT8_MAX);
			difference = interval(rng);
            difference = difference - mutationDampener * difference;
			new_value = child.color.b + difference;
			child.color.b = std::clamp(new_value, 0, UINT8_MAX);
			int sum = child.color.r + child.color.g + child.color.b;
			while(sum < 350){
				int index = rng() % 3;
				switch(index){
					case 0:
						child.color.r++;
						break;
					case 1:
						child.color.g++;
						break;
					case 2:
						child.color.b++;
						break;
				}
				sum++;
			}
            return child;
		}
	};
}
