#include "emit_pheromones.hpp"

namespace server {
	void emit_pheromones(Ecs::Entity & entity) {
		auto * emitter = entity.get_if<PheromoneEmitter>();
		auto * movement = entity.get_if<Movement>();
		if(!emitter) return; 
		if(!movement) return;
		for(auto x = -emitter->distance; x < emitter->distance; x++) {
			for(auto y = -emitter->distance; y < emitter->distance; y++) {
				if(emitter->field->in_range(movement->position.x, movement->position.y)) {
					(*emitter->field)[movement->position] += emitter->strenght;
				}
			}
		}
	}
}