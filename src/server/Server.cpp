#include "Server.hpp"
#include <iostream>

namespace server {
	Server::Server() {
		std::cout << "Server starting...\n";
	}



	void Server::run() {
		std::cout << "Server running...\n";
	}
}