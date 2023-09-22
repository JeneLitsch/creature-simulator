#pragma once
#include <cassert>
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "sim/component/EntitySensor.hpp"
#include <iostream>

// based on Code from https://github.com/davidrmiller/biosim4/blob/main/src/getSensor.cpp and https://github.com/davidrmiller/biosim4/blob/main/src/grid.cpp

namespace sim{

    template <typename SensedComponent, EntitySensorAxis axis>
    void update_entity_sensor(EntitySensor<SensedComponent, axis>* sensor, std::vector<Ecs::Entity*> sensed_entities, const EntitySensorConfig& config){
        stx::vector2i loc = sensor->transform->location;
        double sum = 0.0;
        stx::vector2d dir_vec = stx::vector2d{sensor->transform->rotation};
        dir_vec = dir_vec / stx::hypot(dir_vec);
        if(axis == EntitySensorAxis::left_right){
            dir_vec = stx::rotate_90_cw(dir_vec);
        }

        for(Ecs::Entity* other : sensed_entities){
            if (other->has<SensedComponent>()) {
                Transform* transform = other->get_if<Transform>();
                if(!transform) return;
                stx::vector2i tloc = transform->location;

                stx::vector2d offset = stx::vector2d(tloc - loc);
                double proj = dir_vec.x * offset.x + dir_vec.y * offset.y; // Magnitude of projection along dir
                double contrib = proj / (offset.x * offset.x + offset.y * offset.y);
                sum += contrib;
            }
        }

        // convert to -1.0..1.0
        double sensor_val = std::tanh((sum / config.radius) * config.sensibility);

        sensor->value = sensor_val;
    }

    std::vector<Ecs::Entity*> visit_neighborhood(Ecs::Entity& entity, stx::grid2<std::uint64_t>& grid, Ecs& ecs, const EntitySensorConfig& config)
    {
        std::vector<Ecs::Entity*> entities;
        Transform* transform = entity.get_if<Transform>();
        
        if(!transform) return entities;

        stx::vector2i loc = transform->location;
        for (int dx = -std::min<int>(config.radius, loc.x); dx <= std::min<int>(config.radius, (grid.size().x - loc.x) - 1); ++dx) {
            int x = loc.x + dx;
            assert(x >= 0 && x < grid.size().x);
            for (int dy = -std::min<int>(config.radius, loc.y); dy <= std::min<int>(config.radius, (grid.size().y - loc.y) - 1); ++dy) {
                int y = loc.y + dy;
                assert(y >= 0 && y < grid.size().y);
                uint64_t entity_id = grid[{static_cast<std::uint64_t>(x), static_cast<std::uint64_t>(y)}];
                auto* otherEntity = ecs.get_if(entity_id);
                if(otherEntity && stx::vector2i{x, y} != loc){
                    entities.push_back(otherEntity);
                }
            }
        }
        return entities;
    }
}
