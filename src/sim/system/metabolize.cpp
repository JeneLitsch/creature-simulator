#include "metabolize.hpp"

namespace sim {
	void metabolize(Ecs::Entity & entity, const MetabolismConfig& config) {
		auto * stomach = entity.get_if<Stomach>();
		auto * health = entity.get_if<Health>();
		if(!stomach) return;
		if(stomach->food > 0.0){
			stomach->food = std::max(stomach->food - config.natural_food_decay_per_tick, 0.0);
			if(health && health->current_health < 1.0 && stomach -> food > 0.0){
				health->current_health = std::min(health->current_health + config.health_regen_per_tick, 1.0);
				stomach->food = std::max(stomach->food - config.food_per_health_regenerated * config.health_regen_per_tick, 0.0);
			}
		}
		else if(health){	
			health->current_health = std::max(health->current_health - config.starving_health_decay_per_tick, 0.0);
		}
	}
}