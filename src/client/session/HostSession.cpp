#include "HostSession.hpp"
#include "client/level/Level.hpp"
#include "server/Server.hpp"

namespace client::session {
	HostSession::HostSession() {}



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
		this->push(std::make_unique<level::Level>(*this));
	}



	HostSession::~HostSession() {
		this->send_request(net::Terminate{});
		this->server_thread.join();
	}



	std::optional<net::Response> HostSession::fetch_response() {
		return this->local_connection.client_fetch();
	}



	void HostSession::send_request(net::Request message) {
		this->local_connection.client_send(std::move(message));
	}
}