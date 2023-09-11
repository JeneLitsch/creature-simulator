#pragma once
#include "client/core/GameState.hpp"
#include "sim/Simulation.hpp"
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "stdxx/chrono.hxx"

namespace client::session {
	class Session;
}

namespace client::level {

	class Level : public core::GameState {
	public:
		Level(session::Session & session, sim::Simulation & simulation);
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	private:
		virtual void on_event(const core::ButtonPressed &) override;
		stx::chrono::every tick_timer;
		
		stx::reference<session::Session> session;
		stx::reference<sim::Simulation> simulation;

		constexpr static inline auto camera_speed = 500.f;
		float camera_zoom = 1.0;
		stx::position2f camera_center;
	};
}
