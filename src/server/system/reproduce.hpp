#pragma once
#include "server/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "server/senses/PheromoneField.hpp"

namespace server{
    void reproduce(stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, Ecs::Entity& entity, MutConfig config);
}