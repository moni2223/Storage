#pragma once
#include "Product.hpp"

/*
We have N section with 5 lines each. Lets think that every product has the same size. So every line can hold 100 things on it.
	Example: Section 1 -> Line 2 -> We have 6 packs of sugar, so we have 4 more spaces to put products.
*/

class StorageCollection {

	Product** products;
	int count;
	int current;
	int currentSection;
	int currentLine;
	void resize();
	void clear();
	int firstFreeIndex();
	void firstFreeSpace(const int quantity);

public:
	StorageCollection();

	void checkAndAddProduct();
	void addProduct(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description, bool add);
	void showProducts();
	void clearProductsByDate(string s);
	void showActivity();
	void exportProduct();

	int writeOnFile(int id);
	int readFromFile();
	int removeFromFile(int line);
	int clearFile();
	int writeActivityOnFile(int functionID);


	bool checkValidDate(string s);
	int* splitDate(string s,string del);

	~StorageCollection();
};