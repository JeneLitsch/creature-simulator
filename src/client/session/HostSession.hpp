#pragma once
#include <future>
#include "client/core/GameState.hpp"
#include "client/core/Socket.hpp"

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
		core::Socket socket;
		net::LocalConnection local_connection;
	};
}