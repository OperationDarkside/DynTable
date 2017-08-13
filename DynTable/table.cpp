#include "table.h"
#include <limits>

namespace dyn {

	table::table() : row_collect (this) {}

	table::table(const std::string _name) : name(_name), row_collect(this) {}

	table::~table() {}


	column_collection & table::columns() {
		return this->col_collect;
	}

	row_collection & table::rows() {
		return this->row_collect;
	}
}