#pragma once
#include <tuple>
#include "ComponentArray.hpp"

namespace core::ecs {
	template<typename ... Components>
	class ComponentManager {
	public:
		template<typename Component>
		void insert(EntityID entity_id, Component component) {
			array_for<Component>().insert(entity_id, component);
		}

		template<typename Component>
		void remove(EntityID entity_id) {
			array_for<Component>().remove(entity_id);
		}

		template<typename Component>
		Component get(EntityID entity_id) {
			return array_for<Component>().get(entity_id);
		}

		void on_entity_delete(EntityID entity_id) {
			auto f = [entity_id](auto & array) {
				array.on_entity_delete(entity_id);
				return 0;
			};
			auto dummy = { (f(array_for<Components>()))... };
		}

	private:
		template<typename Component>
		ComponentArray<Component> & array_for() {
			return std::get<ComponentArray<Component>>(this->arrays);
		}
		
		std::tuple<ComponentArray<Components>...> arrays;
	};
}