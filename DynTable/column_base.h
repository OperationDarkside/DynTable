#pragma once

#ifndef COLUMN_BASE_H
#define COLUMN_BASE_H

#include <string>

namespace dyn {
	class column_base {
	public:
		column_base();
		~column_base();

		void set_name(const std::string _name);
		std::string& get_name();
	private:
		friend class row;
		friend class table;

		virtual void add_value() = 0;

		std::string name;
	};
}
#endif // !COLUMN_BASE_H