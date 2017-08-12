# DynTable

This little table project is inspired by the .NET DataTable.
The idea was to create a dynamic, but (hopefully) memory-leak free, in-ram table.
Data is arranged in templated columns for type-safety and easier searchability.
Finding rows with certain values is supported via lambda-expressions.


### Create a named table

```C++
dyn::table tbl("test table");
```

### Add a column
```C++
tbl.add_column<int>("ID");
```

### Add rows
```C++
dyn::row row = tbl.new_row();
row.set_field(0, 1);
```

### Search with lambdas
```C++
std::vector<dyn::row> rows = tbl.find_rows([](dyn::row r) {return r.get_field<std::string>(1) == "Peter"; });
```
