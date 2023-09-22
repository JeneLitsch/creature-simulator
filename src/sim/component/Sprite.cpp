#include "Sprite.hpp"

namespace sim {
	Sprite Sprite::createChild(std::uint64_t seed, const ReproductionConfig & config, double mutationDampener){
		Xoshiro::Xoshiro256PP rng;
		rng.seed(seed);
		Sprite child = *this;
		
		std::uniform_int_distribution interval { 
			-config.max_color_difference,
			+config.max_color_difference
		};
		
		const int diff_r = interval(rng);
		const int new_r = static_cast<int>(child.color.r + (diff_r - mutationDampener * diff_r));
		
		const int diff_g = interval(rng);
		const int new_g = static_cast<int>(child.color.g + (diff_g - mutationDampener * diff_g));

		const int diff_b = interval(rng);
		const int new_b = static_cast<int>(child.color.b + (diff_b - mutationDampener * diff_b));
		
		child.color.r = static_cast<std::uint8_t>(std::clamp(new_r, 0, UINT8_MAX));
		child.color.g = static_cast<std::uint8_t>(std::clamp(new_g, 0, UINT8_MAX));
		child.color.b = static_cast<std::uint8_t>(std::clamp(new_r, 0, UINT8_MAX));
		
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
}