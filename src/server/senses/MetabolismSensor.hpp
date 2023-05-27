#pragma once
#include "stdxx/reference.hxx"
#include "server/component/Metabolism.hpp"
#include "server/senses/Sensor.hpp"
#include "server/Ecs.hpp"


namespace server {
	class MetabolismSensor : public Sensor {
	public:
		MetabolismSensor(stx::reference<Ecs> ecs, std::uint64_t id, Substance substance);
		virtual double sample(const Params &) const override;

	private:
		stx::reference<Ecs> ecs;
		std::uint64_t id;
		Substance substance;
	};
}