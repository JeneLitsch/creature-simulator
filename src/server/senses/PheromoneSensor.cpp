#include "PheromoneSensor.hpp"

namespace server {
	PheromoneSensor::PheromoneSensor(stx::reference<PheromoneField> field) 
		: field{field} {}



	double PheromoneSensor::sample(const Params & params) const {
		return this->field->sample(params.position);
	}
}