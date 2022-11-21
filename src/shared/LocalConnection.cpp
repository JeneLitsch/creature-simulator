#include "LocalConnection.hpp"

namespace net {
	namespace {
		std::optional<Message> pop(std::queue<net::Message> & queue) {
			if(queue.empty()) return std::nullopt;
			auto msg = std::move(queue.front());
			queue.pop();
			return msg;
		}
	}



	LocalConnection::LocalConnection() {
		
	}



	std::optional<net::Message> LocalConnection::client_fetch() {
		std::lock_guard lock{mutex};
		return pop(this->server_to_client);
	}



	void LocalConnection::client_send(net::Message message) {
		std::lock_guard lock{mutex};
		this->client_to_server.push(std::move(message));
	}



	std::optional<net::Message> LocalConnection::server_fetch() {
		std::lock_guard lock{mutex};
		return pop(this->client_to_server);
	}



	void LocalConnection::server_send(net::Message message) {
		std::lock_guard lock{mutex};
		this->server_to_client.push(std::move(message));
	}
}