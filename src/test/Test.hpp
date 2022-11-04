#pragma once
#include "core/GameState.hpp"

namespace test {
	class Test : public core::GameState {
	public:
		Test();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	};
}