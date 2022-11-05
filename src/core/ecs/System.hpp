#pragma once
#include <set>
#include <bitset>
#include "EntityID.hpp"

namespace core::ecs {
	template<typename Signature>
	class SystemManager;
	

	// Base class for any system 
	template<typename Signature>
	class System {
		// Only the matchin SystemManager may access private stuff
		friend class SystemManager<Signature>;
	public:
		// Set the component as a requiredment for the system. 
		// The flag is then set in the system Signature
		template<typename Component>
		inline void set_required() {
			this->signature.template set<Component>(true);
		}

		// Returns true if the signature (of an entity) matches the systems signature
		inline bool matches(Signature signature) const {
			return (signature.bitset & this->signature.bitset) == this->signature.bitset;
		}

	protected:
		// Entities currently matching the system
		std::set<EntityID> entities;
	private:
		Signature signature;
	};
}