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

int StorageCollection::writeActivityOnFile(int functionID) {
	ofstream file("activity.txt", ios::app);
	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return -1;
	}

	switch (functionID) {
	case 1: file << products[current - 1]->get_import_date() << " --> Product with name: " << products[current - 1]->get_name()
		<< " added on section: " << products[current - 1]->get_section() << " line: " << products[current - 1]->get_line() << endl;
		break;
	case 5: file << products[current - 1]->get_expiry_date() << " --> Product with name: " << products[current - 1]->get_name()
		<< "removed from section: " << products[current - 1]->get_section() << " line: " << products[current - 1]->get_line() << endl;
		break;
	default: break;
	}

	if (!file.eof()) cout << "";
	file.close();
}

int StorageCollection::writeOnFile() {

	ofstream file("output.txt", ios::app);

	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return -1;
	}

	file << "{ " << products[current - 1]->get_name() << " " << products[current - 1]->get_expiry_date() << " " << products[current - 1]->get_import_date() << " " << products[current - 1]->get_manufacturer() << " " << products[current - 1]->get_quantity() << " " << products[current - 1]->get_section() << " " << products[current - 1]->get_line() << " }" << "\n";

	if (!file.eof())
		

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

			if (buff.size() < 2) break;

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
			if (buff.size() > 1) {
				original << buff << "\n";

			}
		}
		remove("copy.txt");
	}

	

	return 0;

}

int StorageCollection::clearFile() {
	ofstream ofs;
	ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	return 1;
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

bool StorageCollection::checkValidDate(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (isalpha(s[i])) {
			cout << "Invalid date" << endl;
			return false;
		}
	}
	int occurrences = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != '/')
			continue;
		else ++occurrences;
	}
	if (occurrences != 2) {
		cout << "Invalid date" << endl;
		return false;
	}
	else return true;
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

	if(!checkValidDate(words[1]) || !checkValidDate(words[2])) return;

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
	writeActivityOnFile(1);
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

void StorageCollection::showActivity() {
	string firstDate;
	string secondDate;

	cin.ignore();
	cout << "Please enter start date: ";
	getline(cin, firstDate);
	cout << "Please enter end date: ";
	getline(cin, secondDate);

	if (!checkValidDate(firstDate) || !checkValidDate(secondDate)) return;

	int first[3];
	for (int i = 0; i < 3; i++) first[i] = splitDate(firstDate, "/")[i];

	int second[3];
	for (int i = 0; i < 3; i++) second[i] = splitDate(secondDate, "/")[i];

	Date from_date = { first[2],first[1],first[0] };
	Date to_date = { second[2],second[1],second[0] };

	ifstream file("activity.txt");

	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return;
	}
	bool match = false;


	while (!file.eof())
	{
		string buff;
		while (getline(file, buff)) {

			if (buff.size() < 2) break;

			string space_delimiter = " ";
			string foundDate;
			for (int i = 0; i < buff.size(); i++) {
				if (buff[i] == ' ') {
					foundDate = buff.substr(0, i);
					break;
				}
			}
			int date[3];
			for (int i = 0; i < 3; i++) date[i] = splitDate(foundDate, "/")[i];
			Date found = { date[2],date[1],date[0] };

			if (found.isBetween(from_date, to_date)) {
				match = true;
				cout << buff << endl;
			}
		}
	}
	if (!match) cout << "No activites in this range." << endl;

}

void StorageCollection::clearProductsByDate(string s) {

	if (!checkValidDate(s)) return;


	int exp_date[3];
	for (int i = 0; i < 3; i++) exp_date[i] = splitDate(s, "/")[i];

	Date input_date = { exp_date[2],exp_date[1],exp_date[0] };
	
	bool cleared = false;


	for (int i = 0; i < current; i++) {
		if (products[i]->get_expiry_date().isExpiringSoon(input_date)) {
			cout <<"-> "<< products[i]->get_name() << " on section:" << products[i]->get_section() << " line: " << products[i]->get_line() << " expires soon, so it is removed" << endl;
			cleared = true;
			removeFromFile(i);
			writeActivityOnFile(5);
		}
		delete products[i];
	}
	if (cleared) {
		current = 0;
		count = 1;
		currentLine = 1;
		currentSection = 1;

		readFromFile();
	}
	


	if (!cleared) cout << "-> There is nothing to clear." << endl;
}

StorageCollection::~StorageCollection() {
	clear();
}
