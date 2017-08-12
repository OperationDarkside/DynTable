#include "table.h"
#include <limits>

namespace dyn {

	table::table() {}

	table::table(const std::string _name) :name(_name) {}

	table::~table() {}


	void table::remove_column(size_t index) {
		size_t count = this->columns.size();
		if(count == 0) {
			throw "remove_column: columns empty";
		}
		if(!(count > index)) {
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
		return row(this, std::numeric_limits<size_t>::max());
	}
	/*
	void table::add_row(row & r) {
		size_t pos = this->rows.size();

		if(pos == std::numeric_limits<size_t>::max()) {
			throw "new_row: Max number of rows reached";
		}

		r.pos = pos;

		this->rows.push_back(std::move(r));

		for(auto& c : columns) {
			c.get()->add_value();
		}
	}
	*/
	row & table::add_row() {
		size_t pos = this->rows.size();

		if(pos == std::numeric_limits<size_t>::max()) {
			throw "new_row: Max number of rows reached";
		}

		row row(this, pos);

		this->rows.push_back(std::move(row));

		for(auto& c : columns) {
			c.get()->add_value();
		}

		return this->rows[pos];
	}

	void table::remove_row(size_t index) {
		size_t len = this->rows.size();

		if(!(len > index)) {
			throw "remove_row: index out of range";
		}

		// delete the actual values in the column stores
		for(auto& c : columns) {
			c.get()->remove_value(index);
		}

		// remove the row
		this->rows.erase(this->rows.begin() + index);

		// refresh the position in all the following rows
		--len;
		for(size_t i = index; i < len; ++i) {
			this->rows[i].pos--;
		}
	}

	void table::remove_row(row & r) {
		remove_row(r.pos);
	}

	void table::remove_row(std::function<bool(row)> f) {
		for(auto& r : this->rows) {
			if(f(r)) {
				remove_row(r.pos);
			}
		}
	}

	void table::insert_row(size_t index, row & r) {
		// Insert values into columns
		for(auto& c : this->columns) {
			c.get()->insert_value(index);
		}

		r.pos = index;

		// Insert row itself
		this->rows.insert(this->rows.begin() + index, r);

		// Increase pos in other rows
		size_t len = this->rows.size();
		index++;
		for(size_t i = index; i < len; ++i) {
			this->rows[i].pos++;
		}
	}

	row & table::get_row(size_t i) {
		if(!(this->rows.size() > i)) {
			throw "remove_row: index out of range";
		}

		return this->rows[i];
	}

	std::vector<row> table::find_rows(std::function<bool(row)> f) {
		std::vector<row> res;

		for(auto& r : this->rows) {
			if(f(r)) {
				res.push_back(r);
			}
		}

		return res;
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