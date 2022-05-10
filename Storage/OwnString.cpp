#include "OwnString.hpp"

OwnString::OwnString(const char* s) {
    if (s == nullptr) {
        str = new char[1];
        str = '\0';
        length = 0;
    }
    else {
        s = new char[strlen(s) + 1];
        strcpy(str, s);
        length = strlen(s);
    }
}

OwnString::OwnString() {
    str = new char[1];
    str = '\0';
    length = 0;
}

OwnString::OwnString(const OwnString& other) {
    str = new char[strlen(other.str) + 1];
    strcpy(str, other.str);
    length = other.length;
}

OwnString& OwnString::operator=(const OwnString& other) {
    if (this != &other) {
        free();
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
        length = other.length;
    }
    return *this;
}

int OwnString::get_len() const {
    return length;
}

const char* OwnString::get_str() const {
    return str;
}

void OwnString::concat(const OwnString& other) {
    char* temp = new char[strlen(str) + other.get_len() + 1];
    strcpy(temp, str);
    strcat(temp, other.str);

    delete[] str;
    str = temp;
    length = strlen(str) + other.get_len();
}

OwnString::~OwnString() {
    delete[] str;
    length = 0;
}
