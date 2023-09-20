#pragma once
#include "sim/Ecs.hpp"

namespace client::level {
    void nnConfig(sim::NeuralNetConfig & config);
    void reproductionConfig(sim::ReproductionConfig & config);
    void metabolismConfig(sim::MetabolismConfig & config);
    void Menu(sim::Config & config);
}
