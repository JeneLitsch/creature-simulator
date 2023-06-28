#include "metabolize.hpp"

namespace sim {
	void metabolize(Ecs::Entity & entity, const MetabolismConfig& config) {
		auto * stomach = entity.get_if<Stomach>();
		auto * health = entity.get_if<Health>();
		if(!stomach) return;
		if(stomach->food > 0.0){
			stomach->food = std::max(stomach->food - config.naturalfoodDecayPerTick, 0.0);
			if(health && health->currentHealth < 1.0 && stomach -> food > 0.0){
				health->currentHealth = std::min(health->currentHealth + config.healthRegenPerTick, 1.0);
				stomach->food = std::max(stomach->food - config.foodPerHealthRegenerated * config.healthRegenPerTick, 0.0);
			}
		}
		else if(health){	
			health->currentHealth = std::max(health->currentHealth - config.starvingHealthDecayPerTick, 0.0);
		}
	}
}