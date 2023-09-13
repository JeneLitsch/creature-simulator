#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace hex {
	std::string encode(const std::uint8_t * data, std::size_t size);
	std::vector<std::uint8_t> decode(std::string_view hex);
}
