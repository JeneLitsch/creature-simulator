#include "PheromoneField.hpp"
#include "stdxx/math.hxx"
#include "SFML/Graphics.hpp"

namespace server {
	PheromoneField::PheromoneField(
		stx::size2f size,
		stx::size2u resolution,
		double fluidity,
		double persistence)
		: size{size}
		, resolution{resolution}
		, fluidity{fluidity}
		, persistence{persistence}
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



	void PheromoneField::emit(double value, stx::position2f position, double radius) {
		auto normalized_position = position / stx::position2f{this->size};
		auto local_position = normalized_position * stx::position2f{this->resolution};
		auto cell = stx::vector2i{local_position};

		std::int32_t distance_x = (radius / this->size.x) * this->resolution.x;
		std::int32_t distance_y = (radius / this->size.y) * this->resolution.y;

		for(std::int32_t dx = -distance_x; dx < distance_x; ++dx) {
			for(std::int32_t dy = -distance_y; dy < distance_y; ++dy) {
				auto sample_point = stx::clamp(
					stx::vector2i{
						static_cast<std::int32_t>(cell.x + dx),
						static_cast<std::int32_t>(cell.y + dy)
					},
					stx::vector2i{0},
					stx::vector2i{
						static_cast<std::int32_t>(this->resolution.x) - 1,
						static_cast<std::int32_t>(this->resolution.y) - 1,
					}
				);
				if(this->data.in_range(sample_point)) {
					this->data[sample_point] = std::clamp(
						this->data[sample_point] + value, 0.0, 1.0
					);
				}
			}
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
					for(std::int32_t dy = -distance_y; dy < distance_y; ++dy) {
						auto sample_point = stx::clamp(
							stx::vector2i{x + dx, y + dy},
							stx::vector2i{0},
							stx::vector2i{
								static_cast<std::int32_t>(this->resolution.x) - 1,
								static_cast<std::int32_t>(this->resolution.y) - 1,
							}
						);
						if(old.in_range(sample_point)) {
							new_value += old[sample_point] / static_cast<float>(2 * distance_x * 2 * distance_y);
						}
					}
				}
				auto write_point = stx::vector2i{x, y};
				this->data[write_point] = new_value * this->persistence;
			}
		}
	}



	void PheromoneField::save_as_img(const std::filesystem::path & path) {
		sf::Image image;
		image.create(this->resolution.x, this->resolution.y, sf::Color::Black);
		for(std::int32_t x = 0; x < this->resolution.x; ++x) {
			for(std::int32_t y = 0; y < this->resolution.y; ++y) {
				image.setPixel(x,y, sf::Color{ static_cast<uint8_t>(this->data(x,y) * 255), 0, 0});
			}
		}
		image.saveToFile(path.string());
	}
}