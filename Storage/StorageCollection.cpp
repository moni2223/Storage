#pragma once
#include "StorageCollection.h"

void StorageCollection::clear() {
	for (int i = 0; i < current; i++) {
		delete products[i];
	}
	delete[] products;
	current = count = currentLine = currentSection = 0;
}

void StorageCollection::resize() {
	count *= 2;
	Product** temp = new Product * [count];

	for (int i = 0; i < current; i++) {
		temp[i] = std::move(products[i]);
	}
	for (int i = current; i < count; i++) {
		temp[i] = nullptr;
	}

	delete[] products;
	products = temp;
}

int* StorageCollection::splitDate(string s, string del) {
	int dates[3];
	int start = 0;
	int end = s.find(del);
	int counter = 0;
	while (end != -1) {
		dates[counter] = stoi(s.substr(start, end - start));
		counter++;
		start = end + del.size();
		end = s.find(del, start);
	}
	dates[counter] = stoi(s.substr(start, end - start));
	return dates;
}

int StorageCollection::writeOnFile() {

	ofstream file("output.txt", ios::app);

	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return -1;
	}

	file << "{ " << products[current - 1]->get_name() << " "
		<< products[current - 1]->get_expiry_date() << " " << products[current - 1]->get_import_date() << " "
		<< products[current - 1]->get_manufacturer() << " " << products[current - 1]->get_quantity() << " "
		<< products[current - 1]->get_section() << " " << products[current - 1]->get_line() << " }";
	file << "\n" << endl;

	if (!file.eof()) //check if the file has ended
		cout << "" << endl;

	file.close();
}

int StorageCollection::readFromFile() {

	ifstream file("output.txt");

	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return -1;
	}

	while (!file.eof())
	{
		string buff;
		while (getline(file, buff)) {
			buff.erase(0, 2); //removes first bracket and whitespace
			buff.erase(buff.size() - 2); //removes whitespace and last bracket

			string space_delimiter = " ";
			vector<string> words;

			size_t pos = 0;
			while ((pos = buff.find(space_delimiter)) != string::npos) {
				words.push_back(buff.substr(0, pos));
				buff.erase(0, pos + space_delimiter.length());
			}
			words.push_back(buff);

			const char* name = words[0].c_str();
			const char* manufacturer = words[3].c_str();
			const char* description = words[5].c_str();
			int quantity = stoi(words[4]);
			int exp_date[3];
			int imp_date[3];

			for (int i = 0; i < 3; i++) exp_date[i] = splitDate(words[1], "/")[i];
			for (int i = 0; i < 3; i++) imp_date[i] = splitDate(words[2], "/")[i];

			Date expiry_date = { exp_date[2],exp_date[1],exp_date[0] };
			Date import_date = { imp_date[2],imp_date[1],imp_date[0] };

			addProduct(name, expiry_date, import_date, manufacturer, quantity, description, 0);

		}
	}
}

int StorageCollection::removeFromFile(int line) {

	string input;
	int currentLine = 0;
	ifstream ini_file{ "output.txt" };
	ofstream out_file{ "copy.txt" };

	if (ini_file && out_file) {
		while (getline(ini_file, input)) {
			if (currentLine == line) currentLine++;
			else {
				currentLine++;
				out_file << input << "\n";
			} 
		}
	}
	ini_file.close();
	out_file.close();

	//Now we need to copy temp file to original one

	ofstream original("output.txt", ios::out);
	ifstream temp("copy.txt");
	string buff;

	if (original && temp) {
		while (getline(temp, buff)) {
			original << buff << "\n";
		}
		remove("copy.txt");
	}

	

	return 0;

}

int StorageCollection::firstFreeIndex() {
	for (int i = 0; i < current; i++)
		if (products[i] == nullptr) return i;

	return current;
}

void StorageCollection::firstFreeSpace(const int quantity) {
	int lastProductQuantity = 0;

	if (count > 1) {
		lastProductQuantity = products[current - 1]->get_quantity();
	}

	int freeSpaceOnLine = 100 - lastProductQuantity;

	if (quantity > freeSpaceOnLine) { //check if we have enough space, if we dont we put the product on the next line
		if (currentLine == 5) {//check if this is the last line of the section
			if(currentSection)
			currentSection += 1;
			currentLine = 1;
		}
		else currentLine += 1;
	}
}

StorageCollection::StorageCollection() {
	current = 0;
	count = 1;
	currentLine = 1;
	currentSection = 1;
	products = new Product * [count];

	for (int i = 0; i < count; i++) {
		products[i] = nullptr;
	}
}

void StorageCollection::checkAndAddProduct() {

	string input;
	vector<string> words;
	size_t counter = 1;
	bool finished = false;

	while (!finished) {
		if (counter == 6) finished = true;

		switch (counter) {
		case 1:
			cout << "-> Enter the name of the product: ";
			break;	
		case 2:
			cout << "-> Enter the expiry_date of the product (1/1/1900): ";
			break;
		case 3:
			cout << "-> Enter the import_date of the product: ";
			break;
		case 4:
			cout << "-> Enter manufacturer's name: ";
			break;
		case 5:
			cout << "-> Enter quantity: ";
			break;
		case 6:
			cout << "-> Enter description: ";
			break;
		default:
			cout << "-> bug";
			break;
		}

		getline(cin, input);
		words.push_back(input);
		++counter;
	}

	const char* name = words[0].c_str();
	const char* manufacturer = words[3].c_str();
	const char* description = words[5].c_str();
	int quantity = stoi(words[4]);
	int exp_date[3];
	int imp_date[3];

	for (int i = 0; i < 3; i++) exp_date[i] = splitDate(words[1], "/")[i];
	for (int i = 0; i < 3; i++) imp_date[i] = splitDate(words[2], "/")[i];

	Date expiry_date = { exp_date[2],exp_date[1],exp_date[0] };
	Date import_date = { imp_date[2],imp_date[1],imp_date[0] };

	addProduct(name, expiry_date, import_date, manufacturer, quantity, description, 1);
	

}

void StorageCollection::addProduct(const char* name, Date expiry_date, Date import_date, const char* manufacturer, const int quantity, const char* description,bool add) {
	bool same = false;

	if (current > 0) { //check if there is any products
		for (int i = 0; i < current; i++) {
			if (strcmp(products[i]->get_name(), name) == 0) {
				if (expiry_date.compare(products[i]->get_expiry_date())) {
					same = true;
					products[i]->set_quantity(products[i]->get_quantity() + quantity);
				}
			}
		}
	}

	if (!same) {
		int id = firstFreeIndex();
		firstFreeSpace(quantity);

		Product* obj = new Product(name, expiry_date, import_date, manufacturer, quantity, description, id, currentSection, currentLine);

		if (id >= this->current && this->current >= count / 2) resize();
		products[id] = obj;

		if (id >= this->current)
			++this->current;

		if (add) {
			cout << "-> Product added successfully" << endl;
			writeOnFile();
		}
	}
}

void StorageCollection::showProducts() {
	if (current == 0) cout << "-> No products found" << endl;

	else for (size_t i = 0; i < current; i++) {
		if (products[i] == nullptr) continue;
		else {
			cout << "-> Name of product: " << products[i]->get_name() << endl;
			cout << "-> Expiry date of the product: " << products[i]->get_expiry_date() << endl;
			cout << "-> Import date of the product: " << products[i]->get_import_date() << endl;
			cout << "-> Manufacturer: " << products[i]->get_manufacturer() << endl;
			cout << "-> Quantity: " << products[i]->get_quantity() << " packages" << endl;
			cout << "-> Description: " << products[i]->get_description() << endl;
			cout << "-> Place (section,line): (" << products[i]->get_section() << "," << products[i]->get_line() << ")" << endl;
			cout << endl;
		}
	}
}

void StorageCollection::clearProductsByDate(string s) {
	
	int exp_date[3];
	for (int i = 0; i < 3; i++) exp_date[i] = splitDate(s, "/")[i];

	Date input_date = { exp_date[2],exp_date[1],exp_date[0] };
	
	bool cleared = false;

	for (int i = 0; i < current; i++) {
		if (products[i]->get_expiry_date().isExpiringSoon(input_date)) {
			cout <<"-> "<< products[i]->get_name() << " on section: " << products[i]->get_section() << " line: " << products[i]->get_line() << "expires soon, so it is removed" << endl;
			products[i] = nullptr;
			cleared = true;
			removeFromFile(i);
		}
	}
	if (!cleared) cout << "-> There is nothing to clear." << endl;
}


StorageCollection::~StorageCollection() {
	clear();
}
