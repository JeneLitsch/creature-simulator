#include "Test.hpp"
#include "core/Ecs.hpp"
#include <iostream>

namespace test {
	struct TestComponent {
		int value = 0;
	};

	struct TestComponent2 {
		int value = 0;
	};

	Test::Test() {
		core::ecs::EntityManager<1> entity_manager;
		const auto entity1 = entity_manager.new_entity();
		const auto entity2 = entity_manager.new_entity();
		const auto entity3 = entity_manager.new_entity();
		const auto entity4 = entity_manager.new_entity();
		std::cout 
			<< entity1 << "\n"
			<< entity2 << "\n"
			<< entity3 << "\n"
			<< entity4 << "\n";
		entity_manager.delete_entity(entity4);
		const auto entity = entity_manager.new_entity();
		std::cout << entity << "\n";


		core::ecs::ComponentArray<TestComponent> component_array;
		component_array.insert(entity1, TestComponent{.value = 42});
		component_array.insert(entity2, TestComponent{.value = 1337});
		component_array.insert(entity3, TestComponent{.value = 420});
		component_array.insert(entity3, TestComponent{.value = 666});

		std::cout 
			<< component_array.get(entity1).value << "\n"
			<< component_array.get(entity2).value << "\n"
			<< component_array.get(entity3).value << "\n";

		core::ecs::ComponentManager<TestComponent, TestComponent2> manager;

		manager.insert(entity1, TestComponent{.value = 42});
		manager.insert(entity1, TestComponent2{.value = 1337});

		std::cout 
			<< manager.get<TestComponent>(entity1).value << "\n"
			<< manager.get<TestComponent2>(entity1).value << "\n";

		manager.on_entity_delete(entity1);
	}



	void Test::update(double dt) {

	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}