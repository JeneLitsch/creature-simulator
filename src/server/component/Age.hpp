#pragma once
#include <cstdint>

namespace server{
    struct Age{
        std::uint64_t age = 0;

        void incrementAge(){
            age++;
        }
    };
}