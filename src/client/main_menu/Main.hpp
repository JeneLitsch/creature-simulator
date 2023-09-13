#pragma once
#include "client/core/GameState.hpp"

namespace client::main_menu {
	class Main : public core::GameState {
	public:
		virtual void update(double dt) override;
		virtual void ui(stx::vector2f window_size) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() { return "Main"; }

	protected:
		virtual void init() override {}
	private:
	};
}