#include "table.h"
#include <iostream>

int main() {
	// Create table with name
	dyn::table tbl("test table");

	// Add columns
	dyn::column_collection& columns = tbl.columns();
	columns.add<int>("ID");
	columns.add<std::string>("Firstname");
	columns.add<std::string>("Lastname");
	columns.add<double>("Cash");

	// Add example rows
	dyn::row_collection& rows = tbl.rows();
	dyn::row row = rows.add();
	row.set_field(0, 1);
	row.set_field<std::string>(1, "Harald");
	row.set_field<std::string>(2, "Schmidt");
	row.set_field(3, 1337.42);
	dyn::row* row1 = &row;

	row = rows.add();
	row.set_field(0, 2);
	row.set_field<std::string>(1, "Peter");
	row.set_field<std::string>(2, "Lustig");
	row.set_field(3, 1111.2222);
	dyn::row* row2 = &row;

	row = rows.add();
	row.set_field(0, 3);
	row.set_field<std::string>(1, "Dieter");
	row.set_field<std::string>(2, "Nua");
	row.set_field(3, 1111.2222);

	row = rows.add();
	row.set_field(0, 4);
	row.set_field<std::string>(1, "Peter");
	row.set_field<std::string>(2, "Faltig");
	row.set_field(3, 12345.6789);

	// Print first and last name
	for(size_t i = 0; i < 3; i++) {
		dyn::row& temp_row = rows[i];

		std::cout << "Firstname:\t" << temp_row.get_field<std::string>(1) << "\nLastname:\t" << temp_row.get_field<std::string>(2) << "\n\n";
	}

	// Find rows where the second field equals "Peter"
	std::vector<dyn::row> rows_found = rows.find([](dyn::row r) {return r.get_field<std::string>(1) == "Peter"; });

	std::cout << "\nFound rows with name \"Peter\":\n\n";
	for(auto& r : rows_found) {
		std::cout << "Firstname:\t" << r.get_field<std::string>(1) << "\nLastname:\t" << r.get_field<std::string>(2) << "\n\n";
	}

	dyn::row r = rows.insert(2);
	r.set_field(0, 77);
	r.set_field<std::string>(1, "Flausen");
	r.set_field<std::string>(2, "Bla");
	r.set_field(3, 111.111);

	rows.remove(1);

	system("pause");
}