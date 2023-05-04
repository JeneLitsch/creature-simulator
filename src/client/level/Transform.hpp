#pragma once
#include "stdxx/vector.hxx"

namespace client::level {
	struct Transform {
		stx::position2f position_prev;
		stx::position2f position_next;

		float rotation_prev = 0.f;
		float rotation_next = 0.f;
		
		float t = 0.f;
	};
}