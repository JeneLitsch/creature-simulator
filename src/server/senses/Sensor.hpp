#pragma once
#include "stdxx/vector.hxx"

namespace server {
	class Sensor {
	public:
		struct Params {
			stx::position2f position;
			double angle;
		};
		virtual double sample(const Params &) const = 0;
		virtual ~Sensor() = default;
	};
}