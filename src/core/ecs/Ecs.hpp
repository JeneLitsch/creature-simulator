#pragma once
#include "index_of.hpp"
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "Signature.hpp"

namespace core::ecs {
	template<typename ... Components>
	class Ecs {
	public:
		// Number of used Components
		constexpr static std::size_t COMPONENT_COUNT = sizeof...(Components);

		// Some typedefs for easier usage
		using Signature = core::ecs::Signature<Components...>;
		using System = core::ecs::System<Signature>;
		using SystemManager = core::ecs::SystemManager<Signature>;
		using EntityManager = core::ecs::EntityManager<Signature>;
		using ComponentManager = core::ecs::ComponentManager<Components...>;



		Ecs() {
			this->system_manager = std::make_unique<SystemManager>();
			this->entity_manager = std::make_unique<EntityManager>();
			this->component_manager = std::make_unique<ComponentManager>();
		}



		EntityID new_entity() {
			return this->entity_manager->new_entity();
		}


		// Removes entity from all systems
		void delete_entity(EntityID entity_id) {
			this->entity_manager->delete_entity(entity_id);
			this->system_manager->on_entity_delete(entity_id);
			this->component_manager->on_entity_delete(entity_id);
		}



		// Adds a component from an entity and updates all affected places.
		template<typename Component>
		void add_component(EntityID entity_id, Component component) {
			// The actual creation of the component
			this->component_manager-> template insert<Component>(entity_id, component);
			
			// Change signature
			auto signature = this->entity_manager->get_signature(entity_id);
			signature.template set<Component>(true);
			this->entity_manager->set_signature(entity_id, signature);
			
			// Refresh systems
			this->system_manager->on_entity_signature_changed(entity_id, signature);
		}



		// Removes a component from an entity and updates all affected places.
		template<typename Component>
		void remove_component(EntityID entity_id) {
			// The actual deletion of the component
			this->component_manager-> template remove<Component>(entity_id);
			
			// Change signature
			auto signature = this->entity_manager->get_signature(entity_id);
			signature.template set<Component>(false);
			this->entity_manager->set_signature(entity_id, signature);
			
			// Refresh systems
			this->system_manager->on_entity_signature_changed(entity_id, signature);
		}



		// Forwards to the component manager
		template<typename Component>
		Component & get_component(EntityID entity_id) {
			return this->component_manager-> template get<Component>(entity_id);
		}



		// Forwards to the system manager
		template<typename SystemType>
		std::shared_ptr<SystemType> new_system() {
			return this->system_manager-> template new_system<SystemType>();
		}



	private:
		std::unique_ptr<SystemManager> system_manager;
		std::unique_ptr<EntityManager> entity_manager;
		std::unique_ptr<ComponentManager> component_manager;
	};
}