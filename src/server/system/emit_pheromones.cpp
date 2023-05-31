#include "emit_pheromones.hpp"

namespace server {
	void emit_pheromones(Ecs::Entity & entity) {
		auto * emitter = entity.get_if<PheromoneEmitter>();
		auto * movement = entity.get_if<Movement>();
		if(!emitter) return; 
		if(!movement) return;
		for(auto dx = -emitter->distance; dx < emitter->distance; dx++) {
			for(auto dy = -emitter->distance; dy < emitter->distance; dy++) {
				auto x = movement->position.x + dx;
				auto y = movement->position.y + dy;
				if(emitter->field->in_range(x, y)) {
					float & value = (*emitter->field)(x, y);
					value = std::clamp(value + static_cast<float>(emitter->strenght), 0.f, 1.f);
				}
			}
		}
	}
}