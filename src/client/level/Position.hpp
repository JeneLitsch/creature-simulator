#pragma once
#include "stdxx/vector.hxx"

namespace client::level {
	struct Position {
		stx::position2f prev;
		stx::position2f next;
		float t = 0.f;
	};
}