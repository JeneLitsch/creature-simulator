#pragma once
#include "stdxx/reference.hxx"
#include "sim/component/Stomach.hpp"
#include "sim/senses/Sensor.hpp"
#include "sim/Ecs.hpp"


namespace sim {
	class MetabolismSensor : public Sensor {
	public:
		MetabolismSensor(stx::reference<Ecs> ecs, std::uint64_t id);
		virtual double sample(const Params &) const override;

	private:
		stx::reference<Ecs> ecs;
		std::uint64_t id;
	};
}