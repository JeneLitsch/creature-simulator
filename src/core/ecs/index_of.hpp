#pragma once
#include <tuple>

namespace core::ecs {
	template <class T, class Tuple>
	struct index_of;

	template <class T, class... Types>
	struct index_of<T, std::tuple<T, Types...>> {
		static const std::size_t value = 0;
	};

	template <class T, class U, class... Types>
	struct index_of<T, std::tuple<U, Types...>> {
		static const std::size_t value = 1 + index_of<T, std::tuple<Types...>>::value;
	};

	template <class T, class... Types>
	std::size_t index_of_v = index_of<T, std::tuple<Types...>>::value;
}