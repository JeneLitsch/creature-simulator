#pragma once
#include "stdxx/reference.hxx"
#include "client/core/GameState.hpp"

namespace client::session {
	class Session;
}

namespace client::level {
	class Level;
	class Edit : public core::GameState {
	public:
		Edit(stx::reference<Level> level);
		virtual void ui(stx::vector2f window_size) final;
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() { return "Edit"; }
	private:
		void use_tool();

		virtual void on_event(const core::MouseMoved &) override;
		virtual void on_event(const core::KeyPressed &) override;
		virtual void init() override;
		stx::reference<Level> level;
		stx::reference<session::Session> session;
		stx::position2i cursor_position;
	};
}