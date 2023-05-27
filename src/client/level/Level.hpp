#pragma once
#include "client/core/GameState.hpp"
#include "server/Simulation.hpp"
#include "stdxx/reference.hxx"
#include "stdxx/chrono.hxx"

namespace client::session {
	class Session;
}

namespace client::level {

	class Level : public core::GameState {
	public:
		Level(session::Session & session, server::Simulation & simulation);
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	private:
		stx::chrono::every tick_timer;
		
		stx::reference<session::Session> session;
		stx::reference<server::Simulation> simulation;
	};
}