#pragma once
#include <random>
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
		std::mt19937_64 rng;
		session::Session & session;
		std::uint64_t simulation_step = 0;
		
		void handle_response(const net::InitState & response);
	};
}