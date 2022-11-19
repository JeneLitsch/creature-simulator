#include "HostSession.hpp"
#include "client/level/Level.hpp"

namespace client::session {
	HostSession::HostSession() {

	}



	void HostSession::update(double dt) {

	}
	
	
	
	void HostSession::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void HostSession::init() {
		this->push(std::make_unique<level::Level>());
	}
}