#include "emit_pheromones.hpp"

namespace server {
	void emit_pheromones(Ecs::Entity & entity) {
		auto pheromone_emitter = entity.get_if<PheromoneEmitter>();
		auto position = entity.get_if<Position>();
		auto rotation = entity.get_if<Rotation>();

		if(!pheromone_emitter) return;
		if(!position) return;
		if(!rotation) return;

		pheromone_emitter->field->emit(
			pheromone_emitter->strenght,
			position->position,
			pheromone_emitter->radius
		);
	}
}