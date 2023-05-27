#include "Level.hpp"
#include "client/session/Session.hpp"
#include "render_grid.hpp"

namespace client::level {

	Level::Level(session::Session & session, server::Simulation & simulation)
		: session{session}
		, simulation{simulation}
		, tick_timer{1.0/10.0} {}



	void Level::update(double dt) {
		if(this->tick_timer(dt)) {
			this->simulation->tick();
		}
	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {
		render_grid(render_target, this->simulation->get_grid(), this->simulation->get_ecs());
	}
	
	
	
	void Level::init() {

	}
}
