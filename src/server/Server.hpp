#pragma once
#include <memory>
#include "shared/LocalConnection.hpp"
#include "Socket.hpp"

namespace server {
	class Server {
	public:
		Server();
		void run();
		void connect_local(net::LocalConnection & local_connection);
	private:
		std::vector<std::unique_ptr<Socket>> sockets;
	};
}