#pragma once
#include <future>
#include "stdxx/chrono.hxx"
#include "server/Simulation.hpp"
#include "client/core/GameState.hpp"

namespace client::session {
	class Session : public core::GameState{
	public:
		Session ();
		void update(double dt) override;
		void render(sf::RenderTarget & render_target) override;
		virtual ~Session () = default;

	protected:
		virtual void init() override {}
	private:
		server::Simulation simulation;
		stx::chrono::every tick_timer;
	};
}