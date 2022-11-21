#include "Server.hpp"
#include <iostream>

namespace server {
	Server::Server() {
		std::cout << "Server starting...\n";
	}



	void Server::run() {
		std::cout << "Server running...\n";
	}



	void Server::connect_local(net::LocalConnection & local_connection) {
		this->sockets.push_back(std::make_unique<Socket>(local_connection));
	}
}