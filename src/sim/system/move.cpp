#include "move.hpp"
#include "stdxx/log.hxx"
#include "sim/Simulation.hpp"
#include <iostream>

namespace sim {
	void move(Ecs::Entity & entity, Ecs & ecs, Simulation& simulation) {
		auto * transform = entity.get_if<Transform>();
		auto * movement = entity.get_if<Movement>();

		if(!transform) return;
		if(!movement) return;
		

		movement->direction.x = rand() % 3 - 1;
		movement->direction.y = rand() % 3 - 1;
		std::uint64_t& id = (*movement->grid)[transform -> location];
		const stx::vector2i from = stx::vector2i{0,0};
		const stx::vector2i to = stx::vector2i{
			static_cast<int>(movement->grid->size().x - 1),
			static_cast<int>(movement->grid->size().y - 1)
		};
		const stx::vector2i new_position = stx::clamp(transform->location + movement->direction, from, to);
		std::uint64_t& other_id = (*movement->grid)[new_position];
		if(other_id < 256){
			transform->location = new_position;
			std::swap(id, other_id);
		}
		else {
			auto * other_entity = ecs.get_if(other_id);
			if(!other_entity) {
				throw std::runtime_error{"Tried to move invalid entity!!!11elf"};
			}
			auto * stomach = entity.get_if<Stomach>();
			auto * edible = other_entity->get_if<Edible>();
			if(edible && stomach) {
				simulation.kill_entity(*other_entity);
				transform->location = new_position;
				std::swap(other_id, id);
				stomach->food += edible->value;
			} 
		}
	}
}