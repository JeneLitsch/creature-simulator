#pragma once
#include <memory>
#include "stdxx/json.hxx"
#include "Ecs.hpp"

namespace sim {
	class Simulation;
	
	void import_entity(stx::json::iterator json, Simulation & sim);
	std::unique_ptr<Simulation> import_simulation(stx::json::iterator json);
}