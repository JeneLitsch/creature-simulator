#pragma once
#include <cstdint>

namespace sim{
    struct Age{
        std::uint64_t age = 0;

        void increment_age(){
            age++;
        }
    };
}