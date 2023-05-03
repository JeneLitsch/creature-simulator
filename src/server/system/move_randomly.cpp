#include "move_randomly.hpp"
#include "stdxx/math.hxx"

namespace server {
	void move_randomly(Ecs::Entity & entity, double dt, std::mt19937_64 & rng) {
		if(!entity.has<Position>()) return;
		if(!entity.has<Rotation>()) return;

		auto & position = entity.get<Position>();
		auto & rotation = entity.get<Rotation>();

		const auto delta = stx::position2f::from_angle((rotation.angle - 90) * M_PI / 180.f);
		position.position = position.position + delta * static_cast<float>(dt) * 100.f;
		position.position = stx::clamp(
			position.position, 
			stx::position2f{0,0},
			stx::position2f{960,540}
		);

		static constexpr auto delta_angle = 400.0f;
		std::uniform_real_distribution<float> dist{-delta_angle, delta_angle};
		rotation.angle += dist(rng) * dt;
		rotation.angle = rotation.angle; 
	}
}