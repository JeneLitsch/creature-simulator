#pragma once
#include <bitset>
#include "index_of.hpp"

namespace core::ecs {
	// Wrapper function around std::bitset for easier access in the context of the Ecs
	template<typename ... Components>
	class Signature {
	public:
		// Sets the flag for the given Component type to true or false
		template<typename Component>
		inline void set(bool b) {
			this->bitset.set(index_of_v<Component, Components...>, b);
		}

		std::bitset<sizeof...(Components)> bitset;
	};
}