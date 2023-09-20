#pragma once
#include "stdxx/math.hxx"

namespace sim {
	class Simulation;
}

namespace client::edit {
	class Effect {
	public:
		virtual void apply(sim::Simulation & sim, stx::position2i position) = 0;
		virtual void clean_up(sim::Simulation & sim) = 0;
		virtual ~Effect() = default;
	};
}
