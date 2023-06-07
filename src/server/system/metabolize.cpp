#include "metabolize.hpp"

namespace server {
	void metabolize(Ecs::Entity & entity) {
		auto * stomach = entity.get_if<Stomach>();
		if(!stomach) return;
		stomach->food = std::max(stomach->food - 0.01, 0.0);
	}
}