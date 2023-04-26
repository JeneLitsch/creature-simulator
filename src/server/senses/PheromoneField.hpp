#pragma once
#include "stdxx/vector.hxx"
#include "stdxx/grid.hxx"
#include "stdxx/oop.hxx"

namespace server {
	class PheromoneField : stx::non_copyable, stx::non_moveable {
	public:
		PheromoneField(stx::size2f size, stx::size2u resolution);
		double sample(const stx::position2f & position) const;

		void fill(double value);
		void set(stx::position2i position, double value);

		void disperse();
	private:
		stx::size2f size;
		stx::size2u resolution;
		stx::grid2<double> data;
	};
}