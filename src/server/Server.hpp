#pragma once
#include <memory>
#include <random>
#include "stdxx/chrono.hxx"
#include "shared/LocalConnection.hpp"
#include "server/Ecs.hpp"
#include "Socket.hpp"

namespace server {
	class Server {
	public:
		Server();
		void run();
		void connect_local(net::LocalConnection & local_connection);
		~Server();
	private:
		void handle_request(Socket & current, const net::Terminate & request);
		void handle_request(Socket & current, const net::Register & request);
		void handle_request(Socket & current, const net::FetchUpdate & request);

		std::vector<std::unique_ptr<Socket>> sockets;
		bool running = true;
		std::uint64_t simulation_step = 0;
		stx::chrono::every tick;
		stx::chrono::clock_d clock;

		static constexpr auto tps = 10;
		static constexpr auto step_time = 1.f / tps;

		Ecs ecs;
		std::mt19937_64 rng;
	};
}