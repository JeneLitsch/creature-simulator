#include "Server.hpp"
#include <iostream>
#include "system/emit_pheromones.hpp"
#include "system/metabolize.hpp"
#include "system/move_randomly.hpp"
#include "system/read_sensors.hpp"
#include "senses/PheromoneSensor.hpp"
#include "senses/MetabolismSensor.hpp"

namespace server {
	Server::Server() 
		: tick{step_time}
		, test_field{{960,540}, {96,54}, 100, 0.9} {
		std::cout << "Server starting...\n";
		this->rng.seed(42);

		// for(std::int32_t x = 0; x < 48; ++x) {
		// 	for(std::int32_t y = 0; y < 54; ++y) {
		// 		this->test_field.set({x,y}, 1.0);
		// 	}
		// }
		std::uniform_real_distribution<float> dist_x{0, 960};
		std::uniform_real_distribution<float> dist_y{0, 540};
		std::uniform_real_distribution<float> dist_rot{0, 360};
		for(std::size_t i = 0; i < 1; ++i) {
			auto & entity = ecs.new_entity();
			entity.add(Rotation{
				.angle = dist_rot(rng)
			});
			entity.add(Position{
				.position = stx::position2f{dist_x(rng), dist_y(rng)}
			});
			entity.add(PheromoneEmitter{
				.field = this->test_field,
				.strenght = 0.1,
				.radius = 50.0,
			});
			auto & sensors = entity.add(Sensors{
				.sensors = {}
			});
			sensors.sensors.push_back(std::make_unique<PheromoneSensor>(this->test_field));
			sensors.sensors.push_back(std::make_unique<MetabolismSensor>(this->ecs, entity.get_id(), Substance::CARBON));
			sensors.sensors.push_back(std::make_unique<MetabolismSensor>(this->ecs, entity.get_id(), Substance::WASTE));
			auto & metabolism = entity.add(Metabolism{});
			metabolism.set(Substance::CARBON, 0.2);
		}
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
				this->ecs.run_system([&] (auto & entity) {
					return move_randomly(entity, this->step_time, this->rng);
				});
				this->ecs.run_system([&] (auto & entity) {
					return read_sensors(entity);
				});
				this->ecs.run_system([&] (auto & entity) {
					return metabolize(entity);
				});
				this->ecs.run_system([&] (auto & entity) {
					return emit_pheromones(entity);
				});
				if(snapshot_rate && (this->simulation_step % snapshot_rate == 0)) {
					this->test_field.save_as_img("tmp/img" + std::to_string(this->simulation_step) + ".png");
				}
				this->test_field.disperse();
				++this->simulation_step;
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