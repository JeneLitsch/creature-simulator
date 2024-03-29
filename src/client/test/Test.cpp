#include "Test.hpp"
#include <iostream>

namespace client::test {

	void test_system(TestEcs::Entity & entity) {
		if(entity.has<TestComponent>()) {
			entity.get<TestComponent>().value++;
		}
	}

	void test_system2(TestEcs::Entity & entity) {
		if(entity.has<TestComponent2>()) {
			entity.get<TestComponent2>().value += 1.f;
		}
	}

	void test_system3(TestEcs::Entity & entity) {
		if(entity.has<TestComponent3>()) {
			entity.get<TestComponent3>().value += 1.f;
		}
	}

	void test_system4(TestEcs::Entity & entity) {
		if(entity.has<TestComponent4>()) {
			entity.get<TestComponent4>().value += 1.f;
		}
	}

	Test::Test() {
		for(std::size_t i = 0; i < 200000; ++i) {
			auto & entity = ecs.new_entity();
			entity.add<TestComponent>(TestComponent{ .value = 1337 });
			entity.add<TestComponent2>(TestComponent2{ .value = 0.f });
			entity.add<TestComponent3>(TestComponent3{ .value = 0.f });
			entity.add<TestComponent4>(TestComponent4{ .value = 0.f });
			// auto & e = ecs.get_by_id(entity.get_id());
		}
	}



	void Test::update(double) {
		this->ecs.clean_up();
		this->ecs.run_system(test_system);
		this->ecs.run_system(test_system2);
		this->ecs.run_system(test_system3);
		this->ecs.run_system(test_system4);
	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}