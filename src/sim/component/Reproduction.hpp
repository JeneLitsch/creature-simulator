#pragma once
#include <random>

namespace sim{
    struct ReproductionConfig{
        uint64_t cooldown = 100;
		double food_cost = 1.0;
        int max_color_difference = 10;
    };

    struct Reproduction{
        uint64_t max_cooldown;
        uint64_t current_cooldown = 0;
        bool wants_to_reproduce = true;

        Reproduction(uint64_t max_cooldown);
        Reproduction(uint64_t max_cooldown, std::uint64_t current_cooldown, bool wants_to_reproduce);

        void incrementCooldown();
    };
}