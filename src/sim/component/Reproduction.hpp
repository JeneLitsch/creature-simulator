#pragma once
#include <random>

namespace sim{
    struct ReproductionConfig{
        uint64_t min_reproduction_cooldown = 100;
        uint64_t max_reproduction_cooldown = 1000;
        uint64_t max_cooldown_difference = 50;
		double food_cost = 1.0;
    };

    struct Reproduction{
        uint64_t max_cooldown;
        uint64_t current_cooldown = 0;
        bool wants_to_reproduce = true;

        Reproduction(uint64_t max_cooldown);

        Reproduction createChild(std::uint64_t seed, const ReproductionConfig & config);
        void incrementCooldown();
    };
}