#pragma once
#include "shared/Ecs.hpp"
#include "client/core/GameState.hpp"

namespace client::test {

	struct TestComponent {
		int value = 0;
	};

	struct TestComponent2 {
		float value = 0.f;
	};

	struct TestComponent3 {
		float value = 0.f;
	};

	struct TestComponent4 {
		float value = 0.f;
	};

	using TestEcs = ecs::Ecs<
		TestComponent,
		TestComponent2,
		TestComponent3,
		TestComponent4
	>;


	

	class Test : public core::GameState {
	public:
		Test();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
		TestEcs ecs;
	};
}