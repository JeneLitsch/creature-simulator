#pragma once
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "sim/senses/PheromoneField.hpp"
#include <random>

namespace sim{
    void reproduce(stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, Ecs::Entity& entity, const Config& config, std::mt19937_64& rng);
}