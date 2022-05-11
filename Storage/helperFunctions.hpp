#pragma once
#include "StorageCollection.h"

void HelpScreen() {
    std::cout << "(1) -> add, (2) -> show, (3) -> export, (4) -> reference, (5) ->cleanUp" << endl;
    std::cout << "Please input the number of the function you want: " << endl;
}

void welcomeScreen() {
    std::cout << "Welcome to our Storage app. Here are the functions you can use:" << endl;
    HelpScreen();
}


