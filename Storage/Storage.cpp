#include "StorageCollection.h"
#include "helperFunctions.hpp"

int main()
{
    StorageCollection s;

    s.readFromFile();

    welcomeScreen();

    char input[1024];
    string str;

    while (cin >> input) {
        switch (input[0]) {
        case '1':
            cin.ignore();
            s.checkAndAddProduct();
            break;
        case '2':
            s.showProducts(); break;
        case '5':
            cout << "-> Please enter date: ";
            cin.ignore();
            getline(cin, str);
            s.clearProductsByDate(str);
            break;

        default:
            cout << "-> Not valid function.Try again." << endl;
        }
    }
  
    
}
