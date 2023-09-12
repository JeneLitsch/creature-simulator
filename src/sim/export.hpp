#pragma once
#include "stdxx/json.hxx"
#include "Ecs.hpp"

namespace sim {

	class Simulation;

	stx::json::node export_entity(const Ecs::Entity & entity);
	stx::json::node export_sim(const Simulation & ecs);
}