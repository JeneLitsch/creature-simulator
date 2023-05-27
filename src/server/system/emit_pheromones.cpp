#include "emit_pheromones.hpp"

namespace server {
	void emit_pheromones(Ecs::Entity & entity) {
		auto * pheromone_emitter = entity.get_if<PheromoneEmitter>();
		auto * transform = entity.get_if<Transform>();

		if(!pheromone_emitter) return;
		if(!transform) return;

		pheromone_emitter->field->emit(
			pheromone_emitter->strenght,
			transform->position,
			pheromone_emitter->radius
		);
	}
}