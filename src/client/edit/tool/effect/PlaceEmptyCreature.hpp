#pragma once
#include "Effect.hpp"
namespace client::edit {
	
	struct PlaceEmptyCreature : Effect {
		virtual void apply(sim::Simulation & sim, stx::position2i position) override;
		virtual void clean_up(sim::Simulation & sim) override;
	};
}