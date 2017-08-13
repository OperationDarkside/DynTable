#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include <string>
#include <array>
#include <functional>
#include "Column.h"
#include "Row.h"


namespace dyn {
	class table {
	public:
		table();
		table(const std::string _name);
		~table();

		// Columns
		template<typename T>
		void add_column(const std::string& _name);
		void remove_column(size_t index);
		void remove_column(const std::string& _name);
		template<typename T>
		column<T>& get_column(size_t index);
		template<typename T>
		column<T>& get_column(const std::string& _name);

		// Rows
		row& new_row();
		// void add_row(row& r);
		row& add_row();
		void remove_row(size_t index);
		void remove_row(row& r);
		void remove_row(std::function<bool(row)> f);
		void insert_row(size_t index, row& r);
		row& get_row(size_t index);

		std::vector<row> find_rows(std::function<bool(row)> f);

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
	template<typename T>
	inline column<T>& table::get_column(size_t index) {
		return this->columns[index];
	}
	template<typename T>
	inline column<T>& table::get_column(const std::string & _name) {
		column_base* col_base = this->columns[get_col_index(_name)].get();
		column<T>* col = static_cast<column<T>*>(col_base);

		if(col == nullptr) {
			throw "get_column: Type mismatch!";
		}

		return col;
	}
}
#endif // !TABLE_H