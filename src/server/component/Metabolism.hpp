#pragma once
#include <unordered_map>

namespace server {
	enum class Substance {
		CARBON, WASTE
	};
	class Metabolism {
	public:
		double get(Substance substance) const;
		void set(Substance substance, double value);
		void change(Substance substance, double d_value);
	private:
		std::unordered_map<Substance, double> substances;
	};
}