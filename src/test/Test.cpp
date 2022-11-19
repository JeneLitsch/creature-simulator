#include "Test.hpp"
#include <iostream>

namespace test {


	

	Test::Test() {
		this->system1 = ecs.new_system<TestSystem1>();
		this->system2 = ecs.new_system<TestSystem2>();
		this->system3 = ecs.new_system<TestSystem3>();
		this->system4 = ecs.new_system<TestSystem4>();


		for(std::size_t i = 0; i < 200000; ++i) {
			const auto entity = ecs.new_entity();		
			ecs.add_component(entity, TestComponent{.value = 42});
			ecs.add_component(entity, TestComponent2{.value = 0.f});
			ecs.add_component(entity, TestComponent3{.value = 0.f});
			ecs.add_component(entity, TestComponent4{.value = 0.f});
		} 
	}



	void Test::update(double dt) {
		this->system1->run(ecs);
		this->system2->run(ecs);
		this->system3->run(ecs);
		this->system4->run(ecs);
	}



	void Test::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Test::init() {}
}