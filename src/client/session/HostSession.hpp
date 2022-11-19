#pragma once
#include "client/core/GameState.hpp"

namespace client::session {
	class HostSession : public core::GameState {
	public:
		HostSession();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	};
}