#pragma once
#include <optional>
#include <queue>
#include <mutex>
#include "comm_protocol.hpp"

namespace net {
	class LocalConnection {
	public:
		LocalConnection();

		std::optional<net::Message> client_fetch();
		void client_send(net::Message message);

		std::optional<net::Message> server_fetch();
		void server_send(net::Message message);
	private:
		std::queue<net::Message> client_to_server;
		std::queue<net::Message> server_to_client;
		std::mutex mutex;
	};
}