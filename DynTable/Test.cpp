#include "table.h"
#include <iostream>

int main() {
	// Create table with name
	dyn::table tbl("test table");

	// Add columns
	tbl.add_column<int>("ID");
	tbl.add_column<std::string>("Firstname");
	tbl.add_column<std::string>("Lastname");
	tbl.add_column<double>("Cash");

	// Add example rows
	dyn::row row = tbl.add_row();
	row.set_field(0, 1);
	row.set_field<std::string>(1, "Harald");
	row.set_field<std::string>(2, "Schmidt");
	row.set_field(3, 1337.42);
	dyn::row* row1 = &row;

	row = tbl.add_row();
	row.set_field(0, 2);
	row.set_field<std::string>(1, "Peter");
	row.set_field<std::string>(2, "Lustig");
	row.set_field(3, 1111.2222);
	dyn::row* row2 = &row;

	row = tbl.add_row();
	row.set_field(0, 3);
	row.set_field<std::string>(1, "Dieter");
	row.set_field<std::string>(2, "Nua");
	row.set_field(3, 1111.2222);

	row = tbl.add_row();
	row.set_field(0, 4);
	row.set_field<std::string>(1, "Peter");
	row.set_field<std::string>(2, "Faltig");
	row.set_field(3, 12345.6789);

	// Print first and last name
	for(size_t i = 0; i < 3; i++) {
		dyn::row& temp_row = tbl.get_row(i);

		std::cout << "Firstname:\t" << temp_row.get_field<std::string>(1) << "\nLastname:\t" << temp_row.get_field<std::string>(2) << "\n\n";
	}

	// Find rows where the second field equals "Peter"
	std::vector<dyn::row> rows = tbl.find_rows([](dyn::row r) {return r.get_field<std::string>(1) == "Peter"; });

	std::cout << "\nFound rows with name \"Peter\":\n\n";
	for(auto& r : rows) {
		std::cout << "Firstname:\t" << r.get_field<std::string>(1) << "\nLastname:\t" << r.get_field<std::string>(2) << "\n\n";
	}

	dyn::row r = tbl.new_row();
	tbl.insert_row(2, r);
	r.set_field(0, 77);
	r.set_field<std::string>(1, "Flausen");
	r.set_field<std::string>(2, "Bla");
	r.set_field(3, 111.111);

	tbl.remove_row(1);

	system("pause");
}