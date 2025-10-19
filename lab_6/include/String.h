#ifndef STRING_H
#define STRING_H

#include "exceptions/Exception.h"
#include "exceptions/MemoryAllocationException.h"
#include "exceptions/IndexOutOfBoundsException.h"
#include "exceptions/InvalidArgumentException.h"
#include "exceptions/OverflowException.h"
#include <iostream>

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
    
    friend bool operator==(const String &lhs, const String &rhs) {
        if (&lhs == &rhs)
            return true;
        if (lhs.length != rhs.length)
            return false;
        for (int i = 0; i < lhs.length; i++) {
            if (lhs.data[i] != rhs.data[i])
                return false;
        }
        return true;
    }
    
    const char& operator[](int index) const;
    
    int getLength() const { return length; }

    friend void print(const String &);
    friend void input(String &);
};

#endif