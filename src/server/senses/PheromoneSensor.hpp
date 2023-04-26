#pragma once
#include "stdxx/reference.hxx"
#include "server/senses/Sensor.hpp"
#include "server/senses/PheromoneField.hpp"


namespace server {
	class PheromoneSensor : public Sensor {
	public:
		PheromoneSensor(stx::reference<PheromoneField> field);
		virtual double sample(stx::position2f position, double angle) const override;
	private:
		stx::reference<PheromoneField> field;
	};
}