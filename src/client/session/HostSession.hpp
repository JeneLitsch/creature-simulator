#pragma once
#include <future>
#include "client/session/Session.hpp"
#include "shared/LocalConnection.hpp"

namespace client::session {
	class HostSession : public Session {
	public:
		HostSession();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
		virtual ~HostSession();

		virtual std::optional<net::Response> fetch_response() override;
		virtual void send_request(net::Request message) override;
	protected:
		virtual void init() override;
	private:
		std::thread server_thread;
		net::LocalConnection local_connection;
		std::uint64_t simulation_step = 0;
	};
}