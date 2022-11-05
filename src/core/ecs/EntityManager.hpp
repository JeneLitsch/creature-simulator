#pragma once
#include <cstdint>
#include <bitset>
#include <queue>
#include "EntityID.hpp"

namespace core::ecs {

	template<typename Signature>
	class EntityManager {
	public:
		EntityManager(std::size_t reserve = 0) {
			this->signatures.reserve(reserve);
		}


		// Creates a new entity and returns its id.
		// Previously freed slots are reused
		EntityID new_entity() {
			if(this->reuseable_ids.empty()) {
				this->signatures.push_back(Signature{});
				return this->signatures.size() - 1;
			}
			else {
				auto id = this->reuseable_ids.front();
				this->reuseable_ids.pop();
				return id;
			}
		}



		// Deletes entity and marks its id as reusable
		void delete_entity(EntityID id) {
			this->signatures[id].reset();
			this->reuseable_ids.push(id);
		}


		
		// Change the signature of an entity
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