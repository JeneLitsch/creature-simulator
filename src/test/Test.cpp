#include "Test.hpp"
#include "core/Ecs.hpp"
#include <iostream>

namespace test {

	struct TestComponent {
		int value = 0;
	};

	struct TestComponent2 {
		std::string value = "";
	};

	using TestEcs = core::ecs::Ecs<TestComponent, TestComponent2>;

	struct TestSystem : core::ecs::System<TestEcs::Signature> {
		TestSystem() {
			this->set_required<TestComponent>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				std::cout << ecs.get_component<TestComponent>(entity).value << "\n";
			}
		}
	};


	struct TestSystem2 : core::ecs::System<TestEcs::Signature> {
		TestSystem2() {
			this->set_required<TestComponent2>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				std::cout << ecs.get_component<TestComponent2>(entity).value << "\n";
			}
		}
	};
	

	Test::Test() {
		TestEcs ecs;
		auto test_system = ecs.new_system<TestSystem>();
		auto test_system2 = ecs.new_system<TestSystem2>();

		const auto entity1 = ecs.new_entity();
		const auto entity2 = ecs.new_entity();
		
		ecs.add_component(entity1, TestComponent{.value = 42});
		ecs.add_component(entity2, TestComponent{.value = 1337});

		ecs.add_component(entity1, TestComponent2{.value = "Hello"});
		ecs.add_component(entity2, TestComponent2{.value = "World"});

				
		test_system->run(ecs);
		test_system2->run(ecs);
	}



	void Test::update(double dt) {

	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}