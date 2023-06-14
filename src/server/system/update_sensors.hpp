#pragma once
#include <cassert>
#include "server/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "server/component/EntitySensor.hpp"

// based on Code from https://github.com/davidrmiller/biosim4/blob/main/src/getSensor.cpp and https://github.com/davidrmiller/biosim4/blob/main/src/grid.cpp

namespace server{
    template <typename SensedComponent, EntitySensorAxis axis>
    void update_entity_sensor(stx::grid2<std::uint64_t>& grid, Ecs& ecs, EntitySensor<SensedComponent, axis>* sensor){
        stx::vector2i loc = sensor->transform->location;
        double sum = 0.0;
        stx::vector2d dirVec = stx::vector2d{sensor->transform->rotation};
        dirVec = dirVec / stx::hypot(dirVec);
        if(axis == EntitySensorAxis.left_right){
            dirVec = stx::rotate_90_cw(dirVec);
        }

        auto f = [&](stx::vector2i tloc) {
            uint64_t entity_id = grid[tloc];
            auto* entity = ecs.get_if(entity_id);
            if (tloc != loc && entity && entity->has<SensedComponent>()) {
                stx::vector2d offset = stx::vector2d(tloc - loc);
                double proj = dirVec.x * offset.x + dirVec.y * offset.y; // Magnitude of projection along dir
                double contrib = proj / (offset.x * offset.x + offset.y * offset.y);
                sum += contrib;
            }
        };

        visitNeighborhood(loc, sensor->radius, f);

        double maxSumMag = 6.0 * sensor->radius;
        assert(sum >= -maxSumMag && sum <= maxSumMag);

        double sensorVal;
        sensorVal = sum / maxSumMag; // convert to -1.0..1.0

        return sensorVal;
    }

    void visitNeighborhood(stx::grid2<std::uint64_t>& grid, stx::vector2i loc, int radius, std::function<void(stx::vector2i)> f)
    {
        for (int dx = -std::min<int>(radius, loc.x); dx <= std::min<int>(radius, (grid.size().x - loc.x) - 1); ++dx) {
            int16_t x = loc.x + dx;
            assert(x >= 0 && x < grid.size().x);
            for (int dy = -std::min<int>(radius, loc.y); dy <= std::min<int>(radius, (grid.size().y - loc.y) - 1); ++dy) {
                int16_t y = loc.y + dy;
                assert(y >= 0 && y < grid.size().y);
                f( stx::vector2i { x, y} );
            }
        }
    }
}