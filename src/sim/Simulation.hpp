#pragma once
#include <memory>
#include <random>
#include <array>
#include "stdxx/grid.hxx"
#include "stdxx/json.hxx"
#include "sim/Ecs.hpp"
#include "sim/senses/PheromoneField.hpp"

namespace sim {
	class Simulation {
	public:
		Simulation();
		void tick();
		const stx::grid2<std::uint64_t> & get_grid() const;
		stx::grid2<std::uint64_t> & get_grid();
		const PheromoneField & get_pheromone_field() const;
		PheromoneField & get_pheromone_field();
		Ecs & get_ecs();
		const Ecs & get_ecs() const;

		void kill_entity(Ecs::Entity& entity);
		~Simulation();
	private:
		sim::Ecs ecs;
		std::mt19937_64 rng;
		stx::grid2<std::uint64_t> grid;
		PheromoneField pheromone_field;
		Config config;
	};
}