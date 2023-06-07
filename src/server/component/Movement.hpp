#pragma once
#include "stdxx/vector.hxx"
#include "stdxx/math.hxx"
#include "stdxx/grid.hxx"
#include "Transform.hpp"

namespace server {
	struct Movement {
		Transform* transform;
		stx::vector2i direction;
		stx::grid2<std::uint64_t>* grid;

		Movement(Transform* pos, stx::grid2<std::uint64_t>* grd): transform{pos}, grid{grd}{}

		void move(){
			direction.x = rand() % 3 - 1;
			direction.y = rand() % 3 - 1;
			std::uint64_t& id = (*grid)[transform -> location];
			const stx::vector2i from = stx::vector2i{0,0};
			const stx::vector2i to = stx::vector2i{
				static_cast<int>(grid->size().x - 1),
				static_cast<int>(grid->size().y - 1)
			};
			const stx::vector2i new_position = stx::clamp(transform -> location + direction, from, to);
			std::uint64_t& other_id = (*grid)[new_position];
			if(other_id < 256){
				transform -> location = new_position;
				std::swap(id, other_id);
			}
		}
	};
}