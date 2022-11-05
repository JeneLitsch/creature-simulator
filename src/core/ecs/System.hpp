#pragma once
#include <set>
#include <bitset>
#include "EntityID.hpp"

namespace core::ecs {
	template<typename Signature>
	class System {
	public:
		std::set<EntityID> entities;
		Signature signature;
	};
}