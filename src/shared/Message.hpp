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

	struct FetchUpdate {
		std::uint64_t simulation_step;
	};

	struct InitState {
		std::uint64_t simulation_step;
	};

	struct UpdateState {
		std::uint64_t simulation_step;
	};

	using Request = std::variant<
		Terminate,
		Register,
		FetchUpdate 
	>;

	using Response = std::variant<
		InitState,
		UpdateState
	>;
}