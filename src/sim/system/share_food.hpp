#pragma once
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"

namespace sim{
    void share_food(Ecs::Entity& entity, const stx::grid2<std::uint64_t>& grid, Ecs* ecs, const Config& config);
}