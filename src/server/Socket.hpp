#pragma once
#include <optional>
#include "shared/LocalConnection.hpp"

namespace server {
	class Socket {
	public:
		Socket(net::LocalConnection & connection);
		std::optional<net::Request> fetch_request();
		void send_response(net::Response message);

		std::uint64_t get_simulation_step() const;
		void update_simulation_step(std::uint64_t step); 
	private:
		net::LocalConnection & connection;
		std::uint64_t simulation_step;
	};
}