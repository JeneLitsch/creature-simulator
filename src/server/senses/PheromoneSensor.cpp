#include "PheromoneSensor.hpp"

namespace server {
	PheromoneSensor::PheromoneSensor(stx::reference<PheromoneField> field) 
		: field{field} {}



	double PheromoneSensor::sample(stx::position2f position, double angle) const {
		return this->field->sample(position);
	}
}