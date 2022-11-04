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
			// Call for each element in tuple
			static constexpr auto f = [](auto & array, auto entity_id) {
				array.on_entity_delete(entity_id);
				// Dummy return value. The return value cannot be void or the fold expression will not work. 
				return 0;
			};
			// Use fold expression while creating a dummy intializer_list. 
			auto dummy = { (f(array_for<Components>(), entity_id))... };
		}

	private:
		// Returns the array for a given Component type
		template<typename Component>
		ComponentArray<Component> & array_for() {
			return std::get<ComponentArray<Component>>(this->arrays);
		}
		
		// A ComponentArray for each Component type.
		std::tuple<ComponentArray<Components>...> arrays;
	};
}