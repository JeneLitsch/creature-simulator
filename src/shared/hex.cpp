#include "hex.hpp"
#include "stdxx/iterator_range.hxx"
#include <sstream>
#include <iomanip>

namespace hex {
	std::string encode(const std::uint8_t * data, std::size_t size) {
		std::ostringstream oss;
		oss << std::hex;
		for(const auto c : stx::iterator_range(data, data+size)) {
			oss << ((int(c) >> 4) & 0xf);
			oss << ((int(c) >> 0) & 0xf);
		}
		return oss.str();
	}



	std::vector<std::uint8_t> decode(std::string_view hex) {
		std::vector<std::uint8_t> bytes;

		for (unsigned int i = 0; i < std::size(hex); i += 2) {
			std::string sub_str = std::string{hex.substr(i, 2)};
			std::uint8_t byte = static_cast<std::uint8_t>(strtol(sub_str.c_str(), NULL, 16));
			bytes.push_back(byte);
		}

		return bytes;
	}
}