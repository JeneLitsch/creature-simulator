#include "Socket.hpp"

namespace client::core {
	Socket::Socket(net::LocalConnection & connection)
	: connection{connection} {}



	std::optional<net::Response> Socket::fetch_response() {
		return this->connection.client_fetch();
	}



	void Socket::send_request(net::Request message) {
		this->connection.client_send(std::move(message));
	}
}