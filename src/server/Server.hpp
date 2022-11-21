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
		~Server();
	private:
		void handle_request(const net::Terminate & terminate);
		std::vector<std::unique_ptr<Socket>> sockets;
		bool running = true; 
	};
}