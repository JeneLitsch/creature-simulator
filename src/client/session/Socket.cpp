#include "Socket.hpp"

namespace client::session {
	Socket::Socket(net::LocalConnection & connection)
	: connection{connection} {}



	std::optional<net::Message> Socket::fetch_message() {
		return this->connection.client_fetch();
	}



	void Socket::send_message(net::Message message) {
		this->connection.client_send(std::move(message));
	}
}