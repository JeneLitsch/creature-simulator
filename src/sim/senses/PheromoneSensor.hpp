#pragma once
#include "stdxx/reference.hxx"
#include "sim/senses/Sensor.hpp"
#include "sim/senses/PheromoneField.hpp"


namespace sim {
	class PheromoneSensor : public Sensor {
	public:
		PheromoneSensor(stx::reference<PheromoneField> field);
		virtual double sample(const Params &) const override;
	private:
		stx::reference<PheromoneField> field;
	};
}