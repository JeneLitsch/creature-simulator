#pragma once
#include <unordered_map>

namespace server {
	enum class Nutrient {
		CARBON,
	};
	class Metabolism {
	public:
		double get(Nutrient nutrient) const;
		void set(Nutrient nutrient, double value);
		void change(Nutrient nutrient, double d_value);
	private:
		std::unordered_map<Nutrient, double> nutrients;
	};
}