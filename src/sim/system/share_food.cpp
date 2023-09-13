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
            if(stomach->food < config.metabolism.foodShared)
                    break;
            for(int j = -1; j<=1; j++){
                if(stomach->food < config.metabolism.foodShared)
                    break;
                stx::vector2i otherPos = transform->location + stx::vector2i{i, j};
                if(otherPos == transform->location || otherPos.x < from.x || otherPos.y < from.y || otherPos.x > to.x || otherPos.y > to.y)
                    continue;
                const std::uint64_t& otherID = grid[otherPos];
                auto * otherEntity = ecs->get_if(otherID);
                if(!otherEntity){
                    continue;
                }
                if(Stomach* otherStomach = otherEntity->get_if<Stomach>()){
                    if(otherStomach->food + config.metabolism.foodShared > config.metabolism.maxStomach){
                        continue;
                    }
                    stomach->food -= config.metabolism.foodShared;
                    otherStomach->food += config.metabolism.foodShared;
                }
            }
        }
    }
}