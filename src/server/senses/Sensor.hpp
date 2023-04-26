#pragma once
#include "stdxx/vector.hxx"

namespace server {
	class Sensor {
	public:
		virtual double sample(stx::position2f position, double angle) const = 0;
		virtual ~Sensor() = default;
	};
}