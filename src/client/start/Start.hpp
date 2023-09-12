#pragma once
#include "client/core/GameState.hpp"

namespace client::start {
	class Start : public core::GameState {
	public:
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;

	protected:
		virtual void init() override {}
	private:
	};
}