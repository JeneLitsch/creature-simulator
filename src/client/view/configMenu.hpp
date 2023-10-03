#pragma once
#include "sim/Ecs.hpp"

namespace client::view {
    void Menu(uint16_t & tickspeed, sim::Config & config);
    void ui_config(sim::Config & config);
}
