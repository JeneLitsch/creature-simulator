#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "EntityID.hpp"

namespace core::ecs {
	template<typename Component>
	class ComponentArray {
	public:

		void insert(EntityID entity_id, Component component) {
			// Reassign component
			if(this->to_component_index.contains(entity_id)) {
				const auto index = this->to_component_index.at(entity_id);
				this->components[index] = component;
			}

			// Create new component
			else {
				const auto index = this->components.size();
				this->components.push_back(component);
				this->to_component_index[entity_id] = index;
			}
		}

		
		
		void remove(EntityID entity_id) {
			if(this->to_component_index.contains(entity_id)) {
				const auto index = this->to_component_index.at(entity_id);
				this->reuseable_ids.push(index);
				this->to_component_index.erase(entity_id);
			}
		}



		Component & get(EntityID entity_id) {
			return this->components[to_component_index[entity_id]];
		}



		void on_entity_delete(EntityID entity_id) {
			this->remove(entity_id);
		}
		
	private:
		std::size_t get_index(EntityID entity_id) {

		}

		std::vector<Component> components;
		std::queue<std::size_t> reuseable_ids;
		std::unordered_map<EntityID, std::size_t> to_component_index;
	};
}