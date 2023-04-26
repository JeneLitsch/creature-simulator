#include "PheromoneField.hpp"
#include "stdxx/math.hxx"

namespace server {
	PheromoneField::PheromoneField(stx::size2f size, stx::size2u resolution)
		: size{size}
		, resolution{resolution}
		, data{resolution, 0.0} {}
	
	
	
	double PheromoneField::sample(const stx::position2f & position) const {
		auto normalized_position = position / stx::position2f{this->size};
		auto local_position = normalized_position * stx::position2f{this->resolution};
		auto cell = stx::vector2i{local_position};
		// std::cout << cell << "\n";
		if(this->data.in_range(cell)) {
			return this->data[cell];
		}
		else {
			return 0.0;
		}
	}



	void PheromoneField::fill(double value) {
		for(auto & cell : this->data) {
			cell = value;
		}
	}



	void PheromoneField::set(stx::position2i position, double value) {
		auto normalized_position = stx::vector2f{position} / stx::vector2f{this->size};
		auto local_position = normalized_position * stx::vector2f{this->resolution};
		auto cell = stx::vector2i{position};
		// std::cout << cell << "\n";
		if(this->data.in_range(cell)) {
			this->data[cell] = value;
		}
	}



	void PheromoneField::disperse() {
		double fluidity = 100;
		std::int32_t distance_x = (fluidity / this->size.x) * this->resolution.x;
		std::int32_t distance_y = (fluidity / this->size.y) * this->resolution.y;
		stx::grid2<double> old = this->data;
		for(std::int32_t x = 0; x < this->resolution.x; ++x) {
			for(std::int32_t y = 0; y < this->resolution.y; ++y) {
				double new_value = 0.0;				
				for(std::int32_t dx = -distance_x; dx < distance_x; ++dx) {
					for(std::int32_t dy = -distance_x; dy < distance_x; ++dy) {
						auto sample_point = stx::clamp(
							stx::vector2i{x + dx, y + dy},
							stx::vector2i{0},
							stx::vector2i{this->resolution}
						);
						if(old.in_range(sample_point)) {
							new_value += old[sample_point] / static_cast<float>(2 * distance_x * 2 * distance_y);
						}
					}
				}
				auto write_point = stx::clamp(
					stx::vector2i{x, y},
					stx::vector2i{0},
					stx::vector2i{this->resolution}
				);
				this->data[write_point] = new_value;
			}
		}
	}
}