#pragma once
#include "core/GameState.hpp"
#include "core/Ecs.hpp"

namespace test {
	struct TestComponent {
		int value = 0;
	};

	struct TestComponent2 {
		float value = 0.f;
	};

	struct TestComponent3 {
		float value = 0;
	};

	struct TestComponent4 {
		float value = 0.f;
	};

	using TestEcs = core::ecs::Ecs<
		TestComponent,
		TestComponent2,
		TestComponent3,
		TestComponent4
	>;
	
	struct TestSystem1 : core::ecs::System<TestEcs::Signature> {
		TestSystem1() {
			this->set_required<TestComponent>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				ecs.get_component<TestComponent2>(entity).value++;
			}
		}
	};


	struct TestSystem2 : core::ecs::System<TestEcs::Signature> {
		TestSystem2() {
			this->set_required<TestComponent2>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				ecs.get_component<TestComponent2>(entity).value += 1.f;
			}
		}
	};


	struct TestSystem3 : core::ecs::System<TestEcs::Signature> {
		TestSystem3() {
			this->set_required<TestComponent3>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				ecs.get_component<TestComponent2>(entity).value += 1.f;
			}
		}
	};


	struct TestSystem4 : core::ecs::System<TestEcs::Signature> {
		TestSystem4() {
			this->set_required<TestComponent4>();
		}
		void run(TestEcs & ecs) {
			for (auto const & entity : this->entities) {
				ecs.get_component<TestComponent2>(entity).value += 1.f;
			}
		}
	};

	class Test : public core::GameState {
	public:
		Test();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
		TestEcs ecs;
		std::shared_ptr<TestSystem1> system1;
		std::shared_ptr<TestSystem2> system2;
		std::shared_ptr<TestSystem3> system3;
		std::shared_ptr<TestSystem4> system4;
	};
}