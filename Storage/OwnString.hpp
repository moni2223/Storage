#pragma once
#include <cstring>

class OwnString {
private:
    int length;
    char* str;
    void free();
public:
    OwnString(const char* str);
    OwnString();

    OwnString(const OwnString& other);
    OwnString& operator=(const OwnString& other);

    int get_len() const;
    const char* get_str() const;

    void concat(const OwnString& other);

    ~OwnString();

};
