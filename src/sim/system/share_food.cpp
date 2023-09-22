#include "share_food.hpp"

namespace sim{
    void share_food(Ecs::Entity& entity, const stx::grid2<std::uint64_t>& grid, Ecs* ecs, const Config& config){
        auto * transform = entity.get_if<Transform>();
        auto * stomach = entity.get_if<Stomach>();
        
        if(!transform) return;
        if(!stomach) return;

        const stx::vector2i from = stx::vector2i{0,0};
		const stx::vector2i to = stx::vector2i{
			static_cast<int>(grid.size().x - 1),
			static_cast<int>(grid.size().y - 1)
		};
        for(int i = -1; i<=1; i++){
            if(stomach->food < config.metabolism.food_shared)
                    break;
            for(int j = -1; j<=1; j++){
                if(stomach->food < config.metabolism.food_shared)
                    break;
                stx::vector2i other_pos = transform->location + stx::vector2i{i, j};
                if(other_pos == transform->location || other_pos.x < from.x || other_pos.y < from.y || other_pos.x > to.x || other_pos.y > to.y)
                    continue;
                const std::uint64_t& other_id = grid[other_pos];
                auto * other_entity = ecs->get_if(other_id);
                if(!other_entity){
                    continue;
                }
                if(Stomach* other_stomach = other_entity->get_if<Stomach>()){
                    if(other_stomach->food + config.metabolism.food_shared > config.metabolism.max_stomach){
                        continue;
                    }
                    stomach->food -= config.metabolism.food_shared;
                    other_stomach->food += config.metabolism.food_shared;
                }
            }
        }
    }
}