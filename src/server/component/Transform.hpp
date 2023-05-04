#pragma once
#include "stdxx/vector.hxx"

namespace server {
	struct Transform {
		stx::position2f position;
		float angle = 0.f;
	};
}