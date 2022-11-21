#pragma once
#include <random>
#include "client/core/GameState.hpp"
#include "client/level/Ecs.hpp"

namespace client::level {

	class Level : public core::GameState {
	public:
		Level();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	private:
		Ecs ecs;
		sf::Texture creature_texture;
		std::mt19937_64 rng;
	};
}