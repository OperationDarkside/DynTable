#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include <string>
#include <functional>
#include "Column.h"
#include "Row.h"


namespace dyn {
	class table {
	public:
		table();
		table(const std::string _name);
		~table();

		template<typename T>
		void add_column(const std::string& _name);
		void remove_column(size_t pos);
		void remove_column(const std::string& _name);

		row& new_row();
		void remove_row(size_t i);
		row& get_row(size_t i);

		std::vector<row> find_rows(std::function<bool (row)> f);

	private:
		friend class row;
		std::string name;
		std::vector<std::unique_ptr<column_base>> columns;
		std::vector<row> rows;

		size_t get_col_index(const std::string _name);
	};

	template<typename T>
	inline void table::add_column(const std::string& _name) {
		//static_assert(std::is_base_of<ColumnBase,Col>::value == false, "Not derived from ColumnBase!");

		if(this->columns.size() == (std::numeric_limits<size_t>::max() - 1)) {
			throw "Max number of columns reached";
		}

		std::unique_ptr<column_base> col = std::make_unique<column<T>>();
		col.get()->set_name(name);

		this->columns.push_back(std::move(col));
	}
}
#endif // !TABLE_H