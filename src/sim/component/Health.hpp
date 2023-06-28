#pragma once

namespace sim {
	struct Health {
		double currentHealth = 0.f;

        bool isDead(){
            return currentHealth <= 0;
        }
	};
}