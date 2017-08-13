#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "column_collection.h"
#include "row_collection.h"


namespace dyn {
	class table {
	public:
		table();
		table(const std::string _name);
		~table();

		column_collection& columns(void);

		row_collection& rows(void);

	private:
		friend class row;

		std::string name;

		column_collection col_collect;

		row_collection row_collect;

		//std::vector<row> row_storage;
	};
}
#endif // !TABLE_H