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

	struct TestSystem : core::ecs::System<2> {
		TestSystem() {
			this->signature.set(0, true);
		}
		void run(core::ecs::Ecs<TestComponent, TestComponent2> & ecs) {
			std::cout << this->entities.size() << "\n";
			for (auto const & entity : this->entities) {
				std::cout << ecs.get_component<TestComponent>(entity).value << "\n";
			}
		}
	};

	Test::Test() {
		core::ecs::Ecs<TestComponent, TestComponent2> ecs;
		auto test_system = ecs.new_system<TestSystem>();
		const auto entity1 = ecs.new_entity();
		ecs.add_component(entity1, TestComponent{.value = 42});
		const auto entity2 = ecs.new_entity();
		ecs.add_component(entity2, TestComponent{.value = 1337});
		test_system->run(ecs);
	}



	void Test::update(double dt) {

	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}