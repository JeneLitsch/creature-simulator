#pragma once
#include <future>
#include "client/core/GameState.hpp"
#include "client/session/Socket.hpp"

namespace client::session {
	class HostSession : public core::GameState {
	public:
		HostSession();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual ~HostSession();
	protected:
		virtual void init() override;
		std::thread server_thread;
		Socket socket;
		net::LocalConnection local_connection;
	};
}