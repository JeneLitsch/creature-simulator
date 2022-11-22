#pragma once
#include <cstdint>
#include <variant>
#include <string>
#include <vector>

namespace net {
	struct Terminate {};

	struct Register {
		std::string name;
	};

	struct InitState {
		std::uint64_t simulation_step;
	};

	using Request = std::variant<
		Terminate,
		Register	 
	>;

	using Response = std::variant<
		InitState
	>;
}