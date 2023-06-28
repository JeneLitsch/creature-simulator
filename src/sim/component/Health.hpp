#pragma once

namespace sim {
	struct Health {
		double currentHealth = 1.f;

        bool isDead(){
            return currentHealth <= 0;
        }
	};
}