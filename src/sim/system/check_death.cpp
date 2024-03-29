#include "stdxx/log.hxx"
#include "check_death.hpp"
#include "sim/Simulation.hpp"

namespace sim {
	void check_death(Ecs::Entity & entity, Simulation& simulation, const Config& config){
        Health* health = entity.get_if<Health>();
        Age* age = entity.get_if<Age>();
        if((health && health->current_health <= 0.0) || (age && age->age > config.max_age)){
            simulation.kill_entity(entity);
        }
    }
}