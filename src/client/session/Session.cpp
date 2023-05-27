#include "Session.hpp"
#include "client/level/Level.hpp"

namespace client::session {
	Session::Session () 
		: tick_timer{1.0/10.0} {}



	void Session::update(double dt) {
		if(this->tick_timer(dt)) {
			this->simulation.tick();
		}
	}
	
	
	
	void Session::render(sf::RenderTarget & render_target) {

	}
}