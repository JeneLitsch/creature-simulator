#pragma once
#include <memory>
#include <array>
#include "stdxx/grid.hxx"
#include "stdxx/json.hxx"
#include "sim/Ecs.hpp"
#include "stdxx/grid.hxx"
#include "sim/senses/PheromoneField.hpp"
#include "WorldPreset.hpp"
#include "shared/random/xoshiro256.h"

namespace sim {
	class Simulation {
	public:
		void tick();
		const stx::grid2<std::uint64_t> & get_grid() const;
		stx::grid2<std::uint64_t> & get_grid();
		const PheromoneField & get_pheromone_field() const;
		PheromoneField & get_pheromone_field();
		Ecs & get_ecs();
		const Ecs & get_ecs() const;

		void kill_entity(Ecs::Entity& entity);
		Config config;
		uint64_t tickCounter = 0;
		~Simulation();

		static std::unique_ptr<Simulation> generate(const WorldPreset & preset);
		static std::unique_ptr<Simulation> empty(stx::size2u32 size);

		sim::Ecs ecs;
        Xoshiro::Xoshiro256PP rng;
		stx::grid2<std::uint64_t> grid;
		PheromoneField pheromone_field;
	private:
		Simulation(stx::size2u32 size);
	};
}
