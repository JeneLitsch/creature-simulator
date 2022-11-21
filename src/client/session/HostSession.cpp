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
		this->server_thread = std::thread {[&] {
			server::Server server;
			server.connect_local(this->local_connection);
			server.run();
		}};
		this->push(std::make_unique<level::Level>(this->socket));
	}



	HostSession::~HostSession() {
		this->socket.send_request(net::Terminate{});
		this->server_thread.join();
	}
}