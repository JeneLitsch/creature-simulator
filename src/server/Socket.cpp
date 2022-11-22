#include "Socket.hpp"

namespace server {
	Socket::Socket(net::LocalConnection & connection)
	: connection{connection} {}



	std::optional<net::Request> Socket::fetch_request() {
		return this->connection.server_fetch();
	}



	void Socket::send_response(net::Response message) {
		this->connection.server_send(std::move(message));
	}



	std::uint64_t Socket::get_simulation_step() const {
		return this->simulation_step;
	}
	
	
	
	void Socket::update_simulation_step(std::uint64_t step) {
		this->simulation_step = step;
	}
}