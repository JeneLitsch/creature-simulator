#pragma once
#include "client/core/GameState.hpp"
#include "client/level/Ecs.hpp"
#include "shared/Message.hpp"

namespace client::session {
	class Session;
};

namespace client::level {

	class Level : public core::GameState {
	public:
		Level(session::Session & session);
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	private:
		Ecs ecs;
		sf::Texture creature_texture;
		session::Session & session;
		std::int32_t tps = 10;
		
		void handle_response(const net::InitState & response);
		void handle_response(const net::UpdateState & response);
	};
}