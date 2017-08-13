#include "column_collection.h"

namespace dyn {
	column_collection::column_collection() {}
	column_collection::~column_collection() {}

	void column_collection::remove(size_t index) {
		size_t count = this->column_storage.size();
		if(count == 0) {
			throw "remove_column: columns empty";
		}
		if(!(count > index)) {
			throw "remove_column: index out of range";
		}
		this->column_storage.erase(this->column_storage.begin() + index);
	}

	void column_collection::remove(const std::string & _name) {
		size_t num = this->get_col_index(_name);
		if(num != std::numeric_limits<size_t>::max()) {
			remove(num);
		} else {
			throw "remove_column: column name not found";
		}
	}
	size_t column_collection::get_col_index(const std::string _name) {
		size_t count = this->column_storage.size();

		for(size_t i = 0; i < count; i++) {
			if(this->column_storage[i].get()->get_name() == _name) {
				return i;
			}
		}
		return std::numeric_limits<size_t>::max();
	}
}