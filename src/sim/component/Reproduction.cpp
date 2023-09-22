#include "Reproduction.hpp"
#include <algorithm>
#include "xoshiro256.h"
#include "stdxx/vector.hxx"

namespace sim{
	Reproduction::Reproduction(uint64_t max_cooldown): max_cooldown(max_cooldown){}

    Reproduction::Reproduction(uint64_t max_cooldown, std::uint64_t current_cooldown, bool wants_to_reproduce) 
		: max_cooldown{max_cooldown}
		, current_cooldown{current_cooldown}
		, wants_to_reproduce{wants_to_reproduce} {}

	void Reproduction::incrementCooldown(){
		current_cooldown++;
	}
}
