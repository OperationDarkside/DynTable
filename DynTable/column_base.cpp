#include "column_base.h"

namespace dyn {

	column_base::column_base() {}


	column_base::~column_base() {}

	void column_base::set_name(const std::string _name) {
		name = _name;
	}
	std::string & column_base::get_name() {
		return this->name;
	}
}