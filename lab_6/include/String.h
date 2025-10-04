#ifndef STRING_H
#define STRING_H

#include "Exception.h"
#include <iostream>
#include <cstring>

class String {
private:
    char *data;
    int length = 0;
    static const int MAX_LENGTH = 1000;

    void freeMemory();
    void copyFrom(const char* str, int strLength);

public:
    String();
    explicit String(const char* str);
    String(const String &other);
    ~String();

    String &operator=(const String &other);
    String &operator+=(const String &other);
    friend bool operator==(const String &lhs, const String &rhs);
    char& operator[](int index);
    const char& operator[](int index) const;
    
    int getLength() const { return length; }
    const char* c_str() const { return data ? data : ""; }

    friend void print(const String &);
    friend void input(String &);
};

bool operator==(const String &lhs, const String &rhs);

#endif