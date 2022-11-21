#include "Server.hpp"
#include <iostream>

namespace server {
	Server::Server() {
		std::cout << "Server starting...\n";
	}



	void Server::run() {
		std::cout << "Server running...\n";
		while(this->running) {
			for(const auto & socket : this->sockets) {
				while(auto request = socket->fetch_request()) {
					std::visit([this](auto & req) {
						this->handle_request(req);
					},
					*request);
				}
			}
		}
	}



	void Server::connect_local(net::LocalConnection & local_connection) {
		this->sockets.push_back(std::make_unique<Socket>(local_connection));
	}



	void Server::handle_request(const net::Terminate & terminate) {
		this->running = false;
	}



	Server::~Server() {
		std::cout << "Server terminated\n";
	}
}