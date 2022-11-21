#include "Socket.hpp"

namespace server {
	Socket::Socket(net::LocalConnection & connection)
	: connection{connection} {}



	std::optional<net::Message> Socket::fetch_message() {
		return this->connection.server_fetch();
	}



	void Socket::send_message(net::Message message) {
		this->connection.server_send(std::move(message));
	}
}