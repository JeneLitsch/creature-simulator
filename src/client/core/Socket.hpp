#pragma once
#include <optional>
#include "shared/LocalConnection.hpp"

namespace client::core {
	class Socket {
	public:
		Socket(net::LocalConnection & connection);
		std::optional<net::Response> fetch_response();
		void send_request(net::Request message); 
	private:
		net::LocalConnection & connection;
	};
}