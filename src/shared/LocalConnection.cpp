#include "LocalConnection.hpp"

namespace net {
	namespace {
		template<typename T>
		std::optional<T> pop(std::queue<T> & queue) {
			if(queue.empty()) return std::nullopt;
			auto msg = std::move(queue.front());
			queue.pop();
			return msg;
		}
	}



	LocalConnection::LocalConnection() {
		
	}



	std::optional<net::Response> LocalConnection::client_fetch() {
		std::lock_guard lock{mutex};
		return pop(this->server_to_client);
	}



	void LocalConnection::client_send(net::Request message) {
		std::lock_guard lock{mutex};
		this->client_to_server.push(std::move(message));
	}



	std::optional<net::Request> LocalConnection::server_fetch() {
		std::lock_guard lock{mutex};
		return pop(this->client_to_server);
	}



	void LocalConnection::server_send(net::Response message) {
		std::lock_guard lock{mutex};
		this->server_to_client.push(std::move(message));
	}
}