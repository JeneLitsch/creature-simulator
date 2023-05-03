#include "metabolize.hpp"

namespace server {
	void metabolize(Ecs::Entity & entity) {
		auto * metabolism = entity.get_if<Metabolism>();
		if(!metabolism) return;
		metabolism->change(Substance::CARBON, -0.1);
		metabolism->change(Substance::WASTE, 0.1);
	}
}