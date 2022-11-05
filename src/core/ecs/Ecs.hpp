#pragma once
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"

namespace core::ecs {
	template <class T, class Tuple>
	struct index_of;

	template <class T, class... Types>
	struct index_of<T, std::tuple<T, Types...>> {
		static const std::size_t value = 0;
	};

	template <class T, class U, class... Types>
	struct index_of<T, std::tuple<U, Types...>> {
		static const std::size_t value = 1 + index_of<T, std::tuple<Types...>>::value;
	};

	template <class T, class... Types>
	std::size_t index_of_v = index_of<T, std::tuple<Types...>>::value;



	template<typename ... Components>
	class Ecs {
	public:
		constexpr static std::size_t COMPONENT_COUNT = sizeof...(Components);

		using Signature = std::bitset<COMPONENT_COUNT>;

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



		void delete_entity(EntityID entity_id) {
			this->entity_manager->delete_entity(entity_id);
			this->system_manager->on_entity_delete(entity_id);
			this->component_manager->on_entity_delete(entity_id);
		}



		template<typename Component>
		void add_component(EntityID entity_id, Component component) {
			this->component_manager-> template insert<Component>(entity_id, component);
			auto signature = this->entity_manager->get_signature(entity_id);
			signature.set(index_of_v<Component, Components...>, true);
			this->entity_manager->set_signature(entity_id, signature);
			this->system_manager->on_entity_signature_changed(entity_id, signature);
		}



		template<typename Component>
		void remove_component(EntityID entity_id) {
			this->component_manager-> template remove<Component>(entity_id);
			auto signature = this->entity_manager->get_signature(entity_id);
			signature.set(index_of_v<Component, Components...>, false);
			this->entity_manager->set_signature(entity_id, signature);
			this->system_manager->on_entity_signature_changed(entity_id, signature);
		}



		template<typename Component>
		Component & get_component(EntityID entity_id) {
			return this->component_manager-> template get<Component>(entity_id);
		}



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