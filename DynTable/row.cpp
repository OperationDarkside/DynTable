#include "Row.h"

namespace dyn {
	row::row(table * _table_ref, size_t _pos) : table_ref(_table_ref), pos(_pos) {}

	row::~row() {}
}