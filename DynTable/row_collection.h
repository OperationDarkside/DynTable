#pragma once
#ifndef ROW_COLLECTION_H
#define ROW_COLLECTION_H

#include <functional>
#include "row.h"

namespace dyn {
	class row_collection {
	public:
		row_collection();
		row_collection(table* _tbl);
		~row_collection();

		/**
		Adds a new row to this collection and returns a reference to it, ready for use
		*/
		row& add();
		/**
		Removes the row at the given index
		*/
		void remove(size_t index);
		/**
		Removes the given row
		*/
		void remove(row& r);
		/**
		Removes the rows that satisfy the given function
		*/
		void remove(std::function<bool(row)> f);
		/**
		Insert the given row at the given index
		*/
		row& insert(size_t index);
		/**
		Returns the rows that satisfy the given function
		*/
		std::vector<row> find(std::function<bool(row)> f);
		/**
		Returns the row at the given index
		*/
		row& operator[](size_t index);
	private:
		table* tbl;
		std::vector<row> row_storage;
	};
}
#endif // !ROW_COLLECTION_H