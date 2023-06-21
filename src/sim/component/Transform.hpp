#pragma once
#include "stdxx/vector.hxx"

namespace sim{
    struct Transform{
        stx::vector2i location;
        stx::vector2i rotation;
    };
}