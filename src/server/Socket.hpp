#pragma once
#include <optional>
#include "shared/LocalConnection.hpp"

namespace server {
	class Socket {
	public:
		Socket(net::LocalConnection & connection);
		std::optional<net::Request> fetch_request();
		void send_response(net::Response message); 
	private:
		net::LocalConnection & connection;
	};
}