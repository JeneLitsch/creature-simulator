#pragma once
#include <cstdint>
#include <variant>

namespace net {
	struct NewEntityCreated {
		std::uint64_t id;
	};

	using Message = std::variant<
		NewEntityCreated 
	>;
}