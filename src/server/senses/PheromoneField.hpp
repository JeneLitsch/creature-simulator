#pragma once
#include <filesystem>
#include "stdxx/vector.hxx"
#include "stdxx/grid.hxx"
#include "stdxx/oop.hxx"

namespace server {
	class PheromoneField : stx::non_copyable, stx::non_moveable {
	public:
		PheromoneField(
			stx::size2f size,
			stx::size2u resolution,
			double fluidity,
			double persistence
		);
		double sample(const stx::position2i & position) const;

		void fill(double value);
		void set(stx::position2i position, double value);

		void disperse();

		void save_as_img(const std::filesystem::path & path);
	private:
		stx::size2f size;
		stx::size2u resolution;
		double fluidity;
		double persistence;
		stx::grid2<double> data;
	};
}