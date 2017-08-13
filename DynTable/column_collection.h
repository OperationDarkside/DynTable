#pragma once
#ifndef COLUMN_COLLECTION_H
#define COLUMN_COLLECTION_H

#include <memory>
#include "column.h"

namespace dyn {
	class column_collection {
	public:
		column_collection();
		~column_collection();

		/**
		Adds a new column with the given name to this table
		*/
		template<typename T>
		void add(const std::string& _name);
		/**
		Removes the column at the given index
		*/
		void remove(size_t index);
		/**
		Removes the column with the given name
		*/
		void remove(const std::string& _name);
		/**
		Returns the column at the given index
		*/
		template<typename T>
		column<T>& operator[](size_t index);
		/**
		Returns the column with the given name
		*/
		template<typename T>
		column<T>& operator[](const std::string& _name);

	private:
		friend class row;
		friend class row_collection;

		std::vector<std::unique_ptr<column_base>> column_storage;

		size_t get_col_index(const std::string _name);
	};


	template<typename T>
	inline void column_collection::add(const std::string & _name) {
		if(this->column_storage.size() == (std::numeric_limits<size_t>::max() - 1)) {
			throw "Max number of columns reached";
		}

		std::unique_ptr<column_base> col = std::make_unique<column<T>>();
		col.get()->set_name(_name);

		this->column_storage.push_back(std::move(col));
	}

	template<typename T>
	inline column<T>& column_collection::operator[](size_t index) {
		column_base* col_base = this->column_storage[index].get();
		column<T>* col = static_cast<column<T>*>(col_base);

		if(col == nullptr) {
			throw "get_column: Type mismatch!";
		}

		return col;
	}

	template<typename T>
	inline column<T>& column_collection::operator[](const std::string & _name) {
		column_base* col_base = this->column_storage[get_col_index(_name)].get();
		column<T>* col = static_cast<column<T>*>(col_base);

		if(col == nullptr) {
			throw "get_column: Type mismatch!";
		}

		return col;
	}
}
#endif // !COLUMN_COLLECTION_H