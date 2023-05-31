#pragma once
#include "stdxx/vector.hxx"
#include "stdxx/math.hxx"
#include "stdxx/grid.hxx"

namespace server {
	struct Movement {
		stx::vector2i position;
		stx::vector2i direction;
		stx::grid2<std::uint64_t>* grid;

		void move(){
			direction.x = rand() % 3 - 1;
			direction.y = rand() % 3 - 1;
			std::uint64_t& id = (*grid)[position];
			stx::vector2i new_position = stx::clamp(position + direction, stx::vector2i{0,0}, stx::vector2i {grid->size().x-1, grid->size().y-1});
			std::uint64_t& other_id = (*grid)[new_position];
			if(other_id < 256){
				position = new_position;
				std::swap(id, other_id);
			}
		}
	};
}