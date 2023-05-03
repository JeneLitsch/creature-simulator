#pragma once
#include <memory>
#include "server/senses/Sensor.hpp"

namespace server {
	struct Sensors {
		std::vector<std::unique_ptr<Sensor>> sensors;
	};
}