#include "emit_pheromones.hpp"

namespace sim {
	void emit_pheromones(Ecs::Entity & entity) {
		auto * emitter = entity.get_if<PheromoneEmitter>();
		auto * transform = entity.get_if<Transform>();
		if(!emitter) return; 
		if(!transform) return;
		emitter->field->emit(stx::position2i{transform->location}, emitter->distance, emitter->composition);
	}
}