#include "table.h"
#include <limits>

namespace dyn {

	table::table() {}

	table::table(const std::string _name) :name(_name) {}

	table::~table() {}


	void table::remove_column(size_t pos) {
		size_t count = this->columns.size();
		if(count == 0) {
			throw "remove_column: columns empty";
		}
		if(!(count > pos)) {
			throw "remove_column: index out of range";
		}
	}

	void table::remove_column(const std::string & _name) {
		size_t num = get_col_index(_name);
		if(num != std::numeric_limits<size_t>::max()) {
			remove_column(num);
		} else {
			throw "remove_column: column name not found";
		}
	}

	row& table::new_row() {
		int pos = this->rows.size();
		row row(this, pos);

		if(this->rows.size() == std::numeric_limits<size_t>::max()) {
			throw "new_row: Max number of rows reached";
		}

		this->rows.push_back(std::move(row));

		for(auto& c : columns) {
			c.get()->add_value();
		}

		return this->rows[pos];
	}

	void table::remove_row(size_t i) {
		if(!(this->rows.size() > i)) {
			throw "remove_row: index out of range";
		}

		this->rows.erase(this->rows.begin() + i);
	}

	row & table::get_row(size_t i) {
		if(!(this->rows.size() > i)) {
			throw "remove_row: index out of range";
		}

		return this->rows[i];
	}

	size_t table::get_col_index(const std::string _name) {
		size_t count = this->columns.size();

		for(size_t i = 0; i < count; i++) {
			if(this->columns[i].get()->name == _name) {
				return i;
			}
		}
		return std::numeric_limits<size_t>::max();
	}
}