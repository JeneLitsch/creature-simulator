#pragma once
#include "stdxx/reference.hxx"
#include "stdxx/grid.hxx"
#include "sim/senses/PheromoneField.hpp"

namespace sim {
	struct PheromoneEmitter {
		stx::reference<PheromoneField> field;
		sf::Color composition;
		std::int32_t distance = 0;
	};
}