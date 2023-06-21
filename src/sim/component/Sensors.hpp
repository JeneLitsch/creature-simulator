#pragma once
#include <memory>
#include "sim/senses/Sensor.hpp"

namespace sim {
	struct Sensors {
		std::vector<std::unique_ptr<Sensor>> sensors;
	};
}