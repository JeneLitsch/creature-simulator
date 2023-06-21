#pragma once
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "sim/senses/PheromoneField.hpp"

namespace sim{
    void reproduce(stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, Ecs::Entity& entity, Config config);
}