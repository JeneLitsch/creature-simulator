#include "hex.hpp"
#include "stdxx/iterator_range.hxx"
#include <sstream>
#include <iomanip>

namespace hex {
	std::string encode(const std::uint8_t * data, std::size_t size) {
		std::ostringstream oss;
		oss << std::setw(2) << std::hex;
		for(const auto c : stx::iterator_range(data, data+size)) {
			oss << int(c);
		}
		return oss.str();
	}



	std::vector<std::uint8_t> decode(const char * string, std::size_t size) {
		return {};
	}
}