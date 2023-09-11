#include "Reproduction.hpp"
#include <algorithm>
#include "stdxx/vector.hxx"

namespace sim{
	Reproduction::Reproduction(uint64_t max_cooldown): max_cooldown(max_cooldown){}

	Reproduction::Reproduction(uint64_t max_cooldown, std::uint64_t current_cooldown, bool wants_to_reproduce) 
		: max_cooldown{max_cooldown}
		, current_cooldown{current_cooldown}
		, wants_to_reproduce{wants_to_reproduce} {}

	Reproduction Reproduction::createChild(std::uint64_t seed, const ReproductionConfig & config) {
		std::mt19937_64 rng;
		rng.seed(seed);
		std::uniform_int_distribution interval { -config.max_cooldown_difference, config.max_cooldown_difference };
		int difference = interval(rng);
		uint64_t new_cooldown;
		if(max_cooldown > -difference){
			new_cooldown = max_cooldown + difference;
		}
		else{
			new_cooldown = config.min_reproduction_cooldown;
		}
		new_cooldown = std::clamp(new_cooldown, config.min_reproduction_cooldown, config.max_reproduction_cooldown);
		current_cooldown = 0;
		return Reproduction{new_cooldown};
	}

	void Reproduction::incrementCooldown(){
		current_cooldown++;
	}
}