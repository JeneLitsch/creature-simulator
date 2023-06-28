#include "reproduce.hpp"

namespace sim{
    void reproduce(stx::grid2<std::uint64_t>* grid, Ecs* ecs, PheromoneField* pheromone_field, Ecs::Entity& entity, const Config& config, std::mt19937_64 & rng){
        auto reproduction_info = entity.get_if<Reproduction>();

        if(reproduction_info && (reproduction_info->current_cooldown >= reproduction_info->max_cooldown && reproduction_info->wants_to_reproduce)){
            const stx::vector2i from = stx::vector2i{0,0};
			const stx::vector2i to = stx::vector2i{
				static_cast<int>(grid->size().x - 1),
				static_cast<int>(grid->size().y - 1)
			};
            Transform* old_transform = entity.get_if<Transform>();
            stx::vector2i new_position;
            bool position_found = false;
            int x;
            int y;
            for(int i = -1; i <= 1; ++i) {
			    for(int j = -1; j <= 1; ++j) {
                    new_position = stx::clamp(old_transform -> location + stx::vector2i{i, j}, from, to);
			        std::uint64_t& other_id = (*grid)[new_position];
			        if(other_id < 256){
                        position_found = true;
                        x = new_position.x;
                        y = new_position.y;
                        break;
                    }
                }
                if(position_found){
                    break;
                }
            }
            if(!position_found){
                return;
            }
            Ecs::Entity& child = ecs -> new_entity();
			auto& transform = child.add(Transform{.location = {x, y}});
			child.add(Movement{&transform, grid});
			child.add(Age{});
            child.add(reproduction_info->createChild(rng(), config.reproduction));
            child.add(Stomach{
				.food = 1.0,
			});
			(*grid)(x,y) = child.get_id();
        }
    }
}