#pragma once
#include "client/core/GameState.hpp"
#include "sim/Simulation.hpp"
#include "stdxx/reference.hxx"
#include "stdxx/math.hxx"
#include "Timer.hpp"


namespace client::session {
	class Session;
}

namespace client::level {

	class Level : public core::GameState {
	public:
		Level(session::Session & session, sim::Simulation & simulation);
		virtual void update(double dt) override;
		virtual void ui(stx::vector2f window_size) final;
		void ui_config();
		void update_camera(double dt);
		virtual void render(sf::RenderTarget & render_target) override;
		virtual const char * name() { return "Level"; }
		sf::View get_camera() const { return this->camera; }
		stx::reference<session::Session> session;
	protected:
		virtual void init() override;

	private:
		virtual void on_event(const core::KeyPressed &) override;
        bool showMenu = true;
        uint16_t tick_speed = 100.0;
		Timer tick_timer;

		double lag = 0.0;
		
		stx::reference<sim::Simulation> simulation;

		constexpr static inline auto camera_speed = 500.f;
		float camera_zoom = 1.0;
		stx::position2f camera_center;

		sf::View camera;

	};
}
