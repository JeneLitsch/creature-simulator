#pragma once
#include "stdxx/vector.hxx"

namespace client::level {
	struct Position {
		stx::position2f next;
		stx::position2f prev;
		float t = 0.f;
	};
}