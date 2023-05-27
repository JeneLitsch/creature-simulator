#include "read_sensors.hpp"
#include "stdxx/io.hxx"
#include "stdxx/iterator.hxx"

namespace server {
	void read_sensors(Ecs::Entity & entity, stx::position2i position) {
		auto sensors = entity.get_if<Sensors>();

		if(!sensors) return;

		Sensor::Params params {
			.position = position,
		};
		
		std::vector<double> output;
		for(const auto & sensor : sensors->sensors) {
			output.push_back(sensor->sample(params));
		}

		std::cout << stx::whole(output) << "\n";
	}
}