#pragma once
#include "shared/Ecs.hpp"
#include "client/core/GameState.hpp"
#include "client/level/Sprite.hpp"
#include "client/level/Position.hpp"

namespace client::level {
	using Ecs =	ecs::Ecs<
		Sprite,
		Position
	>;

	class Level : public core::GameState {
	public:
		Level();
		virtual void update(double dt) override;
		virtual void render(sf::RenderTarget & render_target) override;
	protected:
		virtual void init() override;
	private:
		Ecs ecs;
	};
}