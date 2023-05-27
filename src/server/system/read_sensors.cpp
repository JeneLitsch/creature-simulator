#include "read_sensors.hpp"
#include "stdxx/io.hxx"
#include "stdxx/iterator.hxx"

namespace server {
	void read_sensors(Ecs::Entity & entity) {
		auto sensors = entity.get_if<Sensors>();
		auto transform = entity.get_if<Transform>();

		if(!sensors) return;
		if(!transform) return;

		Sensor::Params params {
			.position = transform->position,
			.angle = transform->angle,
		};
		
		std::vector<double> output;
		for(const auto & sensor : sensors->sensors) {
			output.push_back(sensor->sample(params));
		}

		std::cout << stx::whole(output) << "\n";
	}
}