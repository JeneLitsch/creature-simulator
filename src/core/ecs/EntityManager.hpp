#pragma once
#include <cstdint>
#include <bitset>
#include <queue>
#include "EntityID.hpp"

namespace core::ecs {

	template<std::size_t COMPONENT_COUNT>
	class EntityManager {
	public:
		using Signature = std::bitset<COMPONENT_COUNT>;
		
		EntityManager(std::size_t reserve = 0) {
			this->signatures.reserve(reserve);
		}



		EntityID new_entity() {
			if(this->reuseable_ids.empty()) {
				this->signatures.push_back(0);
				return this->signatures.size() - 1;
			}
			else {
				auto id = this->reuseable_ids.front();
				this->reuseable_ids.pop();
				return id;
			}
		}



		void delete_entity(EntityID id) {
			this->signatures[id].reset();
			this->reuseable_ids.push(id);
		}


		
		void set_signature(EntityID id, Signature signature) {
			this->signatures[id] = signature;
		}



		Signature get_signature(EntityID id) const {
			return this->signatures[id];
		}



	private:
		std::queue<EntityID> reuseable_ids;
		std::vector<Signature> signatures;
	};
}