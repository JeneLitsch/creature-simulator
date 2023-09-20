#pragma once
#include "stdxx/reference.hxx"
#include "Effect.hpp"

namespace client::edit {
	class Edit;

	struct Inspect : Effect {
		Inspect(stx::reference<Edit> edit);
		virtual void apply(sim::Simulation & sim, stx::position2i position) override;
		virtual void clean_up(sim::Simulation & sim) override;

		stx::reference<Edit> edit; 
	};
}