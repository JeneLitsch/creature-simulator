#pragma once
#include "stdxx/reference.hxx"
#include "stdxx/grid.hxx"
#include "server/senses/PheromoneField.hpp"

namespace server {
	struct PheromoneEmitter {
		stx::reference<PheromoneField> field;
		sf::Color composition;
		std::int32_t distance = 0;
	};
}