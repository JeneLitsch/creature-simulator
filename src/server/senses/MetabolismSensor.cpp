#include "MetabolismSensor.hpp"

namespace server {
	MetabolismSensor::MetabolismSensor(stx::reference<Ecs> ecs, std::uint64_t id, Nutrient nutrient)
		: ecs{ecs}
		, id{id}
		, nutrient{nutrient} {}
	
	
	
	double MetabolismSensor::sample(const Params & params) const {
		auto * entity = ecs->get_if(this->id);
		if(!entity) return 0.0;
		auto * metabolism = entity->get_if<Metabolism>();
		if(!metabolism) return 0.0;
		return metabolism->get(this->nutrient);
	}
}