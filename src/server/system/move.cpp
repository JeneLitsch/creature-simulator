#include "move.hpp"
#include "stdxx/log.hxx"

namespace server {
	void move(Ecs::Entity & entity, Ecs & ecs) {
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
			auto & other_entity = ecs.get(other_id);
			if(other_entity.has<Edible>()) {
				stx::log[stx::INFO] << "Entity eaten: " << other_id;
				transform->location = new_position;
				other_id = std::exchange(id, 0);
				other_entity.mark_delete();
			} 
		}
	}
}