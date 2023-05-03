#include "Metabolism.hpp"

namespace server {
	double Metabolism::get(Substance substance) const {
		if(this->substances.contains(substance)) {
			return this->substances.at(substance);
		}
		return 0.0;
	}



	void Metabolism::set(Substance substance, double value) {
		this->substances[substance] = value;
	}



	void Metabolism::change(Substance substance, double d_value) {
		this->set(substance, this->get(substance) + d_value);
	}
}