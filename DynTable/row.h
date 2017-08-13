#pragma once

#ifndef ROW_H
#define ROW_H

#include "column_collection.h"

namespace dyn {
	class row {
	public:
		row(column_collection* _col_collect, size_t _pos);
		~row();

		template<typename T>
		T& get_field(size_t i);

		template<typename T>
		void set_field(size_t i, T val);

		friend bool operator==(const row& row1, const row& row2);
	private:
		friend class row_collection;
		unsigned long long pos = 0;
		column_collection* col_collect;
	};

	template<typename T>
	inline T & row::get_field(size_t i) {
		if(i > (col_collect->column_storage.size() - 1)) {
			throw "get_field: column index out of range";
		}
		column_base* colBase = col_collect->column_storage[i].get();

		column<T>* col = static_cast<column<T>*>(colBase);

		if(col == nullptr) {
			throw "get_field: column type mismatch";
		}

		return col->get_value(pos);
	}

	template<typename T>
	inline void row::set_field(size_t i, T val) {
		if(i > (col_collect->column_storage.size() - 1)) {
			throw "get_field: column index out of range";
		}
		column_base* colBase = col_collect->column_storage[i].get();

		column<T>* col = static_cast<column<T>*>(colBase);

		if(col == nullptr) {
			throw "get_field: column type mismatch";
		}

		col->set_value(val, pos);
	}
}
#endif // !ROW_H