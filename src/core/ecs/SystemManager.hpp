#pragma once
#include "System.hpp"
#include <memory>
#include <vector>

namespace core::ecs {

	template<typename Signature>
	class SystemManager {
	public:
		template<typename SystemType>
		std::shared_ptr<SystemType> new_system() {
			auto system = std::make_shared<SystemType>();
			this->systems.push_back(system);
			return system;
		}


		void on_entity_delete(EntityID entity_id) {
			for(const auto system : this->systems) {
				system->entities.erase(entity_id);
			}
		}



		void on_entity_signature_changed(EntityID entity_id, Signature signature) {
			for(const auto & system : this->systems) {
				if((signature & system->signature) == system->signature) {
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