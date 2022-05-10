#pragma once
#include "StorageCollection.h"

void StorageCollection::clear() {
	for (int i = 0; i < current; i++) {
		delete products[i];
	}
	delete[] products;
	current = 0;
	count = 0;
}

void StorageCollection::resize() {
	count *= 2;
	Product** temp = new Product * [count];

	for (size_t i = 0; i < current; i++) {
		temp[i] = std::move(products[i]);
	}
	for (size_t i = current; i < count; i++) {
		temp[i] = nullptr;
	}
	delete[] products;
	products = temp;
}

int StorageCollection::firstFreeIndex() {
	for (size_t i = 0; i < current; i++)
		if (products[i] == nullptr) return i;

	return current;
}

StorageCollection::StorageCollection() {
	current = 0;
	count = 1;
	lastLine = 0;
	lastSection = 0;

	products = new Product * [count];

	for (int i = 0; i < count; i++) {
		products[i] = nullptr;
	}
}

void StorageCollection::addProduct(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description) {

	int id = firstFreeIndex();
	
	Product * obj = new Product(name, expiry_date, import_date, manufacturer, quantity, description);
	//obj->set_id(id);

	if (id >= this->current && this->current >= count / 2) resize();

	//products[id] = obj ;

	if (id >= this->current)
		++this->current;
}


StorageCollection::~StorageCollection() {
	clear();
}
