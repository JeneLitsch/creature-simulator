#pragma once
#include "stdxx/vector.hxx"
#include "stdxx/math.hxx"
#include "stdxx/grid.hxx"
#include "Transform.hpp"

namespace sim {
	struct Movement {
		Transform* transform;
		stx::vector2i direction;
		stx::grid2<std::uint64_t>* grid;

		Movement(Transform* pos, stx::grid2<std::uint64_t>* grd): transform{pos}, grid{grd}{}
	};
}