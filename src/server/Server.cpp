#include "Server.hpp"
#include <iostream>

namespace server {
	Server::Server() : tick{step_time} {
		std::cout << "Server starting...\n";
	}



	void Server::run() {
		std::cout << "Server running...\n";
		while(this->running) {
			for(const auto & socket : this->sockets) {
				while(auto request = socket->fetch_request()) {
					std::visit([&](auto & req) {
						this->handle_request(*socket, req);
					},
					*request);
				}
			}
			const auto dt = clock();
			if(tick(dt)) {
				++this->simulation_step;
			}
		}
	}



	void Server::connect_local(net::LocalConnection & local_connection) {
		this->sockets.push_back(std::make_unique<Socket>(local_connection));
	}



	void Server::handle_request(Socket & current, const net::Register & request) {
		std::cout << "New user: " << request.name << "\n";
		current.send_response(net::InitState{
			.simulation_step = this->simulation_step
		});
	}



	void Server::handle_request(Socket & current, const net::Terminate & request) {
		this->running = false;
	}



	void Server::handle_request(Socket & current, const net::FetchUpdate & request) {
		if(request.simulation_step < this->simulation_step) {
			current.send_response(net::UpdateState{
				.simulation_step = this->simulation_step
			});
		}
	}



	Server::~Server() {
		std::cout << "Server terminated\n";
	}
}