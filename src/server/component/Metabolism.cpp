#include "Metabolism.hpp"

namespace server {
	double Metabolism::get(Nutrient nutrient) const {
		if(this->nutrients.contains(nutrient)) {
			return this->nutrients.at(nutrient);
		}
		return 0.0;
	}



	void Metabolism::set(Nutrient nutrient, double value) {
		this->nutrients[nutrient] = value;
	}



	void Metabolism::change(Nutrient nutrient, double d_value) {
		this->set(nutrient, this->get(nutrient) + d_value);
	}
}