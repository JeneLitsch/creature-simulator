#pragma once
#include "System.hpp"
#include <memory>
#include <vector>

namespace core::ecs {

	// The system manager holds all the systems of its parent Ecs.
	// It adds and removes entities if they match or not.
	template<typename Signature>
	class SystemManager {
	public:
		// Creates a new system of type SystemType registered to the Systemmanager
		template<typename SystemType>
		std::shared_ptr<SystemType> new_system() {
			auto system = std::make_shared<SystemType>();
			this->systems.push_back(system);
			return system;
		}



		// Removed deleted entities from all registered system
		void on_entity_delete(EntityID entity_id) {
			for(const auto system : this->systems) {
				system->entities.erase(entity_id);
			}
		}



		// Adds or removes entity from systems after its signature changed.
		void on_entity_signature_changed(EntityID entity_id, Signature signature) {
			for(const auto & system : this->systems) {
				if(system->matches(signature)) {
					system->entities.insert(entity_id);
				}
				else {
					system->entities.erase(entity_id);
				}
			}
		}
	private:
		std::vector<std::shared_ptr<System<Signature>>> systems;
	};
}