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
	Product(const char* name, Date expiry_date, Date import_date,  const char* manufacturer, const int quantity, const char* description,const int id, const int section,const int line);

	Product(const Product& other);
	Product& operator=(const Product& other);

	void set_id(const int id);

	~Product();
};