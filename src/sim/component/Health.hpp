#pragma once

namespace sim {
	struct Health {
		double current_health = 1.f;

        bool isDead(){
            return current_health <= 0;
        }
	};
}