#pragma once
#include "stdxx/reference.hxx"
#include "stdxx/grid.hxx"
#include "server/senses/PheromoneField.hpp"

namespace server {
	struct PheromoneEmitter {
		stx::reference<stx::grid2<float>> field;
		double strenght = 0.0;
		std::int32_t distance = 0;
	};
}