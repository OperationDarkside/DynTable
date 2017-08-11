#include "table.h"
#include <iostream>

int main() {
	dyn::table tbl("test table");

	tbl.add_column<int>("ID");
	tbl.add_column<std::string>("Firstname");
	tbl.add_column<std::string>("Lastname");
	tbl.add_column<double>("Cash");

	dyn::row row = tbl.new_row();
	row.set_field(1, 0);
	row.set_field<std::string>("Harald", 1);
	row.set_field<std::string>("Schmidt", 2);
	row.set_field(1337.42, 3);

	dyn::row& temp_row = tbl.get_row(0);

	std::cout << "Firstname:\t" << temp_row.get_field<std::string>(1) << "\nLastname:\t" << temp_row.get_field<std::string>(2);
	system("pause");
}