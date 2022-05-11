#include "Product.hpp"

void Product::free() {
	delete[] name;
	delete[] manufacturer;
	delete[] description;
	quantity = 0;
}

void Product::copyFrom(const Product& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	manufacturer = new char[strlen(other.manufacturer) + 1];
	strcpy(manufacturer, other.manufacturer);

	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);

	quantity = other.quantity;
	expiry_date = other.expiry_date;
	import_date = other.import_date;
	id = other.id;
	section = other.section;
	line = other.line;
}

Product::Product() : expiry_date(), import_date(), quantity(0) {
	name = new char[1];
	name[0] = '\0';

	manufacturer = new char[1];
	manufacturer[0] = '\0';

	description = new char[1];
	description[0] = '\0';

	id = section = line = 0;

}

Product::Product(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description)
	: quantity(quantity), expiry_date(expiry_date), import_date(import_date) {

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->manufacturer = new char[strlen(manufacturer) + 1];
	strcpy(this->manufacturer, manufacturer);

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);

}

Product::Product(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description,const int id, const int section,const int line)
	: expiry_date(expiry_date), import_date(import_date), quantity(quantity), section(section), line(line) {

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->manufacturer = new char[strlen(manufacturer) + 1];
	strcpy(this->manufacturer, manufacturer);

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);

	set_id(id);
}

Product::Product(const Product& other) {
	copyFrom(other);
}

Product& Product::operator=(const Product& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

int Product::get_quantity() const {
	return quantity;
}

char* Product::get_name() const {
	return name;
}

Date Product::get_expiry_date() const {
	return expiry_date;
}

Date Product::get_import_date() const {
	return import_date;
}

char* Product::get_description() const {
	return description;
}

char* Product::get_manufacturer() const {
	return manufacturer;
}

int Product::get_section() const {
	return section;
}

int Product::get_line() const {
	return line;
}


void Product::set_id(const int id) {
	this->id = id;
}

void Product::set_quantity(const int quantity) {
	this->quantity = quantity;
}

Product::~Product() {
	free();
}
