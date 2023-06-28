#pragma once
#include "stdxx/json.hxx"
#include "Ecs.hpp"

namespace sim {
	stx::json::node export_entity(const Ecs::Entity & entity);
	stx::json::node export_ecs(const Ecs & ecs);
}