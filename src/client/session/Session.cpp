#include "Session.hpp"
#include "client/level/Level.hpp"

namespace client::session {
	Session::Session () {}



	void Session::update(double dt) {
		this->push(std::make_unique<level::Level>(*this, this->simulation));
	}
	
	
	
	void Session::render(sf::RenderTarget & render_target) {

	}
}