#include "read_sensors.hpp"
#include "stdxx/io.hxx"
#include "stdxx/iterator.hxx"

namespace server {
	void read_sensors(Ecs::Entity & entity) {
		auto sensors = entity.get_if<Sensors>();
		auto position = entity.get_if<Position>();
		auto rotation = entity.get_if<Rotation>();

		if(!sensors) return;
		if(!position) return;
		if(!rotation) return;

		Sensor::Params params {
			.position = position->position,
			.angle = rotation->angle,
		};
		
		std::vector<double> output;
		for(const auto & sensor : sensors->sensors) {
			output.push_back(sensor->sample(params));
		}

		std::cout << stx::whole(output) << "\n";
	}
}