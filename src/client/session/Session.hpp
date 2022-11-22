#pragma once
#include "shared/LocalConnection.hpp"
#include "client/core/GameState.hpp"

namespace client::session {
	class Session : public core::GameState {
	public:
		virtual std::optional<net::Response> fetch_response() = 0;
		virtual void send_request(net::Request message) = 0; 
	};
}