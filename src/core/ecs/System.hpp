#pragma once
#include <set>
#include <bitset>
#include "EntityID.hpp"

namespace core::ecs {
	template<std::size_t COMPONENT_COUNT>
	class System {
	public:
		std::set<EntityID> entities;
		std::bitset<COMPONENT_COUNT> signature;
	};
}