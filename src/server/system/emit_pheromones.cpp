#include "emit_pheromones.hpp"

namespace server {
	void emit_pheromones(Ecs::Entity & entity) {
		auto * emitter = entity.get_if<PheromoneEmitter>();
		auto * movement = entity.get_if<Movement>();
		if(!emitter) return; 
		if(!movement) return;
		emitter->field->emit(stx::position2i{movement->position}, emitter->distance, emitter->composition);
	}
}