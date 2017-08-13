#include "row_collection.h"
#include "table.h"

namespace dyn {
	row_collection::row_collection() {}
	row_collection::row_collection(table* _tbl) :tbl(_tbl) {}
	row_collection::~row_collection() {}

	row & row_collection::add() {
		size_t pos = this->row_storage.size();

		if(pos == std::numeric_limits<size_t>::max()) {
			throw "new_row: Max number of rows reached";
		}

		row row(&this->tbl->columns(), pos);

		this->row_storage.push_back(std::move(row));

		column_collection& cols = this->tbl->columns();

		for(auto& c : cols.column_storage) {
			c.get()->add_value();
		}

		return this->row_storage[pos];
	}
	void row_collection::remove(size_t index) {
		size_t len = this->row_storage.size();

		if(!(len > index)) {
			throw "remove_row: index out of range";
		}

		// delete the actual values in the column stores
		column_collection& cols = this->tbl->columns();

		for(auto& c : cols.column_storage) {
			c.get()->remove_value(index);
		}

		// remove the row
		this->row_storage.erase(this->row_storage.begin() + index);

		// refresh the position in all the following rows
		--len;
		for(size_t i = index; i < len; ++i) {
			this->row_storage[i].pos--;
		}
	}
	void row_collection::remove(row & r) {
		remove(r.pos);
	}
	void row_collection::remove(std::function<bool(row)> f) {
		for(auto& r : this->row_storage) {
			if(f(r)) {
				remove(r.pos);
			}
		}
	}
	row & row_collection::insert(size_t index) {
		// Insert values into columns
		column_collection& cols = this->tbl->columns();

		for(auto& c : cols.column_storage) {
			c.get()->insert_value(index);
		}

		row r(&this->tbl->columns(), index);

		// Insert row itself
		this->row_storage.insert(this->row_storage.begin() + index, r);

		// Increase pos in other rows
		size_t len = this->row_storage.size();
		for(size_t i = index + 1; i < len; ++i) {
			this->row_storage[i].pos++;
		}

		return this->row_storage[index];
	}
	std::vector<row> row_collection::find(std::function<bool(row)> f) {
		std::vector<row> res;

		for(auto& r : this->row_storage) {
			if(f(r)) {
				res.push_back(r);
			}
		}

		return res;
	}
	row & row_collection::operator[](size_t index) {
		if(!(this->row_storage.size() > index)) {
			throw "operator[]: index out of range";
		}

		return this->row_storage[index];
	}
}