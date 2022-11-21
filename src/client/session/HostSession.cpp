#include "HostSession.hpp"
#include "client/level/Level.hpp"
#include "server/Server.hpp"

namespace client::session {
	HostSession::HostSession()
	: socket{local_connection} {}



	void HostSession::update(double dt) {

	}
	
	
	
	void HostSession::render(sf::RenderTarget & render_target) {

	}
	
	
	
	void HostSession::init() {
		std::promise<void> barrier_p;
		std::future<void> barrier_f = barrier_p.get_future();
		this->server_thread = std::thread {[&] {
			server::Server server;
			server.connect_local(this->local_connection);
			barrier_p.set_value();
			server.run();
		}};
		barrier_f.wait();
		this->push(std::make_unique<level::Level>());
	}



	HostSession::~HostSession() {
		this->server_thread.join();
	}
}