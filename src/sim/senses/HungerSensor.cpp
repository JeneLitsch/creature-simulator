#include "HungerSensor.hpp"

namespace sim {
	MetabolismSensor::MetabolismSensor(stx::reference<Ecs> ecs, std::uint64_t id)
		: ecs{ecs}
		, id{id} {}
	
	
	
	double MetabolismSensor::sample(const Params & params) const {
		auto * entity = ecs->get_if(this->id);
		if(!entity) return 0.0;
		auto * stomach = entity->get_if<Stomach>();
		if(!stomach) return 0.0;
		return std::clamp(1.0 / (stomach->food + 1.0), 0.0, 1.0);
	}
}