#include "disperse_pheromones.hpp"

namespace sim {
	namespace {
		constexpr std::int64_t radius = 1;
		constexpr float stability = 0.97f;

		float sample_surounding(stx::grid2<float> & field, auto x, auto y) {
			float value = 0.f;
			for(auto dx = -radius; dx <= radius; dx++) {
				for(auto dy = -radius; dy <= radius; dy++) {
					const stx::vector2i read_xy {
						std::clamp<int>(static_cast<int>(x+dx), 0, static_cast<int>(field.size().x - 1)),
						std::clamp<int>(static_cast<int>(y+dy), 0, static_cast<int>(field.size().y - 1)),
					};
					value += field[read_xy] / static_cast<float>((radius * 2 + 1) * (radius * 2 + 1));
				}
			}
			return value * stability;
		}
	}



	void disperse_phermones(stx::grid2<float> & field) {
		auto new_grid = field;

		for(auto x = 0; x < field.size().x; x++) {
			for(auto y = 0; y < field.size().y; y++) {
				new_grid[stx::vector2i{x,y}] = sample_surounding(field, x, y);
			}
		}

		field = new_grid;
	}
}