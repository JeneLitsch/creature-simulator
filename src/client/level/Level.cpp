#include "Level.hpp"
#include "client/session/Session.hpp"

namespace client::level {

	Level::Level(session::Session & session, server::Simulation & simulation)
		: session{session}
		, simulation{simulation} {}



	void Level::update(double dt) {

	}
	
	
	
	void Level::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void Level::init() {

	}
}
