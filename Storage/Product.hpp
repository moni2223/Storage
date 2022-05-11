#pragma once
#include "Date.h"

const int MAX_LENGTH = 1024;

class Product {
	char* name = nullptr;
	Date expiry_date;
	Date import_date;
	char* manufacturer = nullptr;
	int quantity;
	char* description = nullptr;
	int id;
	int section;
	int line;

	void free();
	void copyFrom(const Product& other);

public:
	Product();
	Product(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description);
	Product(const char* name, Date expiry_date, Date import_date,  const char* manufacturer, const int quantity, const char* description,const int id, const int section, const int line);

	Product(const Product& other);
	Product& operator=(const Product& other);

	int get_quantity() const;
	char* get_name() const;
	Date get_expiry_date() const;
	Date get_import_date() const;
	char* get_manufacturer() const;
	char* get_description() const;
	int get_section() const;
	int get_line() const;

	void set_id(const int id);
	void set_quantity(const int quantity);

	~Product();
};