#include "move_randomly.hpp"
#include "stdxx/math.hxx"

namespace server {
	void move_randomly(Ecs::Entity & entity, double dt, std::mt19937_64 & rng) {
		if(!entity.has<Transform>()) return;
		
		auto & transform = entity.get<Transform>();

		const auto delta = stx::position2f::from_angle((transform.angle - 90) * M_PI / 180.f);
		transform.position = transform.position + delta * static_cast<float>(dt) * 100.f;
		transform.position = stx::clamp(
			transform.position, 
			stx::position2f{0,0},
			stx::position2f{960,540}
		);

		static constexpr auto delta_angle = 400.0f;
		std::uniform_real_distribution<float> dist{-delta_angle, delta_angle};
		transform.angle += dist(rng) * dt;
		transform.angle = transform.angle; 
	}
}