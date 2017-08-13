#include "Row.h"

namespace dyn {
	row::row(column_collection* _col_collect, size_t _pos) : col_collect(_col_collect), pos(_pos) {
	}

	row::~row() {}

	bool operator==(const row & row1, const row & row2) {
		return row1.pos == row2.pos;
	}
}