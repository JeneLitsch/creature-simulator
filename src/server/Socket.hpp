#pragma once
#include <optional>
#include "shared/LocalConnection.hpp"

namespace server {
	class Socket {
	public:
		Socket(net::LocalConnection & connection);
		std::optional<net::Message> fetch_message();
		void send_message(net::Message message); 
	private:
		net::LocalConnection & connection;
	};
}