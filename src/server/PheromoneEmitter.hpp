#pragma once
#include "senses/PheromoneField.hpp"

namespace server {
	struct PheromoneEmitter {
		stx::reference<PheromoneField> field;
		double strenght = 0.0;
		double radius = 0.0;
	};
}