#pragma once
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "sim/senses/PheromoneField.hpp"
#include <random>

namespace sim{
    void reproduce(Ecs::Entity& entity, stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, const Config& config, Xoshiro::Xoshiro256PP& rng);
}
