#pragma once
#include <cstdint>
#include <variant>
#include <string>
#include <vector>
#include "stdxx/vector.hxx"

namespace net {
	struct Terminate {};

	struct Register {
		std::string name;
	};

	struct FetchUpdate {};

	struct InitState {
		std::uint64_t simulation_step;
		std::vector<std::uint64_t> entities;
		std::vector<std::tuple<std::uint64_t, stx::position2f>> positions;
		std::vector<std::tuple<std::uint64_t, float>> rotations;
	};

	struct UpdateState {
		std::uint64_t simulation_step;
		std::vector<std::tuple<std::uint64_t, stx::position2f>> positions;
		std::vector<std::tuple<std::uint64_t, float>> rotations;
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