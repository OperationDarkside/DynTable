#pragma once
#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include "column_base.h"

namespace dyn {
	template<typename T>
	class column : public column_base {
	public:
		column();
		~column();

	private:
		friend class table;
		friend class row;
		std::vector<T> storage;

		void add_value() override;
		void remove_value(size_t i) override;
		void insert_value(size_t i) override;

		T& get_value(size_t i);
		void set_value(T& val_, size_t i);
	};

	template<typename T>
	inline column<T>::column() {}

	template<typename T>
	inline column<T>::~column() {}

	template<typename T>
	inline void column<T>::add_value() {
		this->storage.push_back(T());
	}

	template<typename T>
	inline void column<T>::remove_value(size_t i) {
		this->storage.erase(this->storage.begin() + i);
	}

	template<typename T>
	inline void column<T>::insert_value(size_t i) {
		this->storage.insert(this->storage.begin() + i, T());
	}

	template<typename T>
	inline T & column<T>::get_value(size_t i) {
		return this->storage[i];
	}

	template<typename T>
	inline void column<T>::set_value(T & val_, size_t i) {
		this->storage[i] = val_;
	}
}
#endif // !COLUMN_H