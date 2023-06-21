#pragma once
#include "stdxx/vector.hxx"
#include "Transform.hpp"

namespace sim{

    enum class EntitySensorAxis{
        front_back,
        left_right
    };

    //Sensor direction is calculated by rotating transform.direction
    //Euler Rotation in degrees
    template <typename SensedComponent, EntitySensorAxis axis>
    struct EntitySensor{
        Transform* transform;
        int radius;
        double value;

        EntitySensor(Transform* transform, int radius) : transform(transform), radius(radius){}
    };
}