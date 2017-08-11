#pragma once

#ifndef ROW_H
#define ROW_H

#include "table.h"

namespace dyn {
	class row {
	public:
		row(table* _table_ref, size_t _pos);
		~row();

		template<typename T>
		T& get_field(size_t i);

		template<typename T>
		void set_field(T val, size_t i);
	private:
		size_t pos = 0;
		table* table_ref;
	};

	template<typename T>
	inline T & row::get_field(size_t i) {
		if(i > (table_ref->columns.size() - 1)) {
			throw "get_field: column index out of range";
		}
		column_base* colBase = table_ref->columns[i].get();

		column<T>* col = static_cast<column<T>*>(colBase);

		if(col == nullptr) {
			throw "get_field: column type mismatch";
		}

		return col->get_value(pos);
	}

	template<typename T>
	inline void row::set_field(T val, size_t i) {
		if(i > (table_ref->columns.size() - 1)) {
			throw "get_field: column index out of range";
		}
		column_base* colBase = table_ref->columns[i].get();

		column<T>* col = static_cast<column<T>*>(colBase);

		if(col == nullptr) {
			throw "get_field: column type mismatch";
		}

		col->set_value(val, pos);
	}
}
#endif // !ROW_H