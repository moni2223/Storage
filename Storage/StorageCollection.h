#pragma once
#include "Product.hpp"


class StorageCollection {

	Product** products;
	int count;
	int current;
	int lastSection;
	int lastLine;
	void resize();
	void clear();
	int firstFreeIndex();

public:
	StorageCollection();

	void addProduct(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description);

	~StorageCollection();
};