#pragma once
#include <cstdint>
#include <variant>
#include <string>

namespace net {
	struct HelloWorld {
		std::string str; 
	};

	struct Terminate {

	};

	using Request = std::variant<
		Terminate	 
	>;

	using Response = std::variant<
		HelloWorld
	>;
}