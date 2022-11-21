#pragma once
#include <optional>
#include <queue>
#include <mutex>
#include "Message.hpp"

namespace net {
	class LocalConnection {
	public:
		LocalConnection();

		std::optional<net::Response> client_fetch();
		void client_send(net::Request message);

		std::optional<net::Request> server_fetch();
		void server_send(net::Response message);
	private:
		std::queue<net::Request> client_to_server;
		std::queue<net::Response> server_to_client;
		std::mutex mutex;
	};
}