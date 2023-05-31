#pragma once
#include <memory>
#include <random>
#include <array>
#include "stdxx/grid.hxx"
#include "server/Ecs.hpp"

namespace server {
	class Simulation {
	public:
		Simulation();
		void tick();
		const stx::grid2<std::uint64_t> & get_grid() const;
		const std::array<stx::grid2<float>, 3> & get_pheromone_fields() const;
		Ecs & get_ecs();
		~Simulation();
	private:
		server::Ecs ecs;
		std::mt19937_64 rng;
		stx::grid2<std::uint64_t> grid;
		std::array<stx::grid2<float>, 3> pheromone_fields; 
	};
}