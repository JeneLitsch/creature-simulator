#include "Server.hpp"
#include <iostream>
#include "move_randomly.hpp"

namespace server {
	namespace {
		void init_entities(Ecs & ecs, auto & rng) {
			std::uniform_real_distribution<float> dist_x{0, 960};
			std::uniform_real_distribution<float> dist_y{0, 540};
			std::uniform_real_distribution<float> dist_rot{0, 360};
			for(std::size_t i = 0; i < 100; ++i) {
				auto & entity = ecs.new_entity();
				entity.add(Rotation{
					.angle = dist_rot(rng)
				});
				entity.add(Position{
					.position = stx::position2f{dist_x(rng), dist_y(rng)}
				});
			}
		}
	}



	Server::Server() : tick{step_time} {
		std::cout << "Server starting...\n";
		this->rng.seed(42);
		init_entities(this->ecs, this->rng);
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
				this->ecs.run_system([&] (auto & entity) {
					return move_randomly(entity, this->step_time, this->rng);
				});
			}
		}
	}



	void Server::connect_local(net::LocalConnection & local_connection) {
		this->sockets.push_back(std::make_unique<Socket>(local_connection));
	}



	void Server::handle_request(Socket & current, const net::Register & request) {
		std::cout << "New user: " << request.name << "\n";
		net::InitState response {
			.simulation_step = this->simulation_step,
			.tps = this->tps,
			.entities = {},
			.positions = {},
			.rotations = {},
		};
		ecs.run_system([&] (Ecs::Entity & entity) {
			const auto id = entity.get_id();
			response.entities.push_back(id);
			if(entity.has<Position>()) {
				response.positions.push_back({
					id,
					entity.get<Position>().position
				});
			}
			if(entity.has<Rotation>()) {
				response.rotations.push_back({
					id,
					entity.get<Rotation>().angle
				});
			}
		});
		current.send_response(std::move(response));
		current.update_simulation_step(this->simulation_step);
	}



	void Server::handle_request(Socket & current, const net::Terminate & request) {
		this->running = false;
	}



	void Server::handle_request(Socket & current, const net::FetchUpdate & request) {
		if(current.get_simulation_step() < this->simulation_step) {
			net::UpdateState response {
				.simulation_step = this->simulation_step,
				.positions = {},
				.rotations = {},
			};
			ecs.run_system([&] (Ecs::Entity & entity) {
				const auto id = entity.get_id();
				if(entity.has<Position>()) {
					response.positions.push_back({
						id,
						entity.get<Position>().position
					});
				}
				if(entity.has<Rotation>()) {
					response.rotations.push_back({
						id,
						entity.get<Rotation>().angle
					});
				}
			});
			current.send_response(std::move(response));
			current.update_simulation_step(this->simulation_step);
		}
	}



	Server::~Server() {
		std::cout << "Server terminated\n";
	}
}