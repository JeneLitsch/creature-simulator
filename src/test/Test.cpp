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

	void test_system(TestEcs::Entity & entity) {
		if(entity.has<TestComponent>()) {
			std::cout << entity.get<TestComponent>().value << "\n";
		}
	}

	void test_system2(TestEcs::Entity & entity) {
		if(entity.has<TestComponent2>()) {
			std::cout << entity.get<TestComponent2>().value << "\n";
		}
	}
	

	Test::Test() {
		TestEcs ecs;

		auto & entity1 = ecs.new_entity();
		auto & entity2 = ecs.new_entity();
		entity1.add<TestComponent>(TestComponent{ .value = 42  });
		entity2.add<TestComponent>(TestComponent{ .value = 1337 });
		entity1.add<TestComponent2>(TestComponent2{ .value = "Hello" });
		entity2.add<TestComponent2>(TestComponent2{ .value = "World" });

		ecs.run_system(test_system);
		ecs.run_system(test_system2);
	}



	void Test::update(double dt) {

	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}