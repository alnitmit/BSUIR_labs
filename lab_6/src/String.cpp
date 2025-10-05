#include "../include/String.h"
#include <iostream>
#include <limits>

void String::freeMemory() {
    delete[] data;
    data = nullptr;
    length = 0;
}

void String::copyFrom(const char* str, int strLength) {
    if (strLength > MAX_LENGTH) {
        throw OverflowException("String length exceeds maximum allowed size");
    }
    
    length = strLength;
    data = new char[length + 1];
    if (!data) {
        throw MemoryAllocationException("Failed to allocate memory for string");
    }
    
    for (int i = 0; i < length; i++) {
        data[i] = str[i];
    }
    data[length] = '\0';
}

String::String() : data(new char[1]) { 
    if (!data) {
        throw MemoryAllocationException("Failed to allocate memory for empty string");
    }
    data[0] = '\0'; 
}

String::String(const char* str) : data(nullptr) {
    if (!str) {
        throw InvalidArgumentException("Null pointer passed to constructor");
    }
    
    // Ручной подсчет длины строки без использования strlen
    int str_len = 0;
    while (str[str_len] != '\0') {
        if (str_len > MAX_LENGTH) {
            throw OverflowException("String length exceeds maximum allowed size");
        }
        str_len++;
    }
    
    copyFrom(str, str_len);
}

String::String(const String &other) : data(nullptr) {
    if (other.data) {
        copyFrom(other.data, other.length);
    } else {
        data = new char[1];
        if (!data) {
            throw MemoryAllocationException("Failed to allocate memory in copy constructor");
        }
        data[0] = '\0';
    }
}

String::~String() { freeMemory(); }

String &String::operator=(const String &other) {
    if (this != &other) {
        freeMemory();
        if (other.data) {
            copyFrom(other.data, other.length);
        } else {
            data = new char[1];
            if (!data) {
                throw MemoryAllocationException("Failed to allocate memory in assignment");
            }
            data[0] = '\0';
            length = 0;
        }
    }
    return *this;
}

String &String::operator+=(const String &other) {
    if (other.data && other.length > 0) {
        int newLength = length + other.length;
        if (newLength > MAX_LENGTH) {
            throw OverflowException("String concatenation would exceed maximum length");
        }
        
        auto newData = new char[newLength + 1];
        if (!newData) {
            throw MemoryAllocationException("Failed to allocate memory for concatenation");
        }

        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }

        for (int i = 0; i < other.length; i++) {
            newData[length + i] = other.data[i];
        }

        newData[newLength] = '\0';

        freeMemory();
        data = newData;
        length = newLength;
    }
    return *this;
}

char& String::operator[](int index) {
    if (index < 0 || index >= length) {
        throw IndexOutOfBoundsException("String index out of bounds: " + std::to_string(index));
    }
    return data[index];
}

const char& String::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw IndexOutOfBoundsException("String index out of bounds: " + std::to_string(index));
    }
    return data[index];
}

void print(const String &str) {
    if (str.data) {
        std::cout << str.data << std::endl;
    }
}

void input(String &string) {
    char ch;
    int length = 0;
    int capacity = 10;
    auto result = new char[capacity];
    if (!result) {
        throw MemoryAllocationException("Failed to allocate initial buffer for input");
    }

    std::cout << "Enter string:" << std::endl;
    while (std::cin.get(ch) && ch != '\n') {
        if (length + 1 >= capacity) {
            if (capacity * 2 > String::MAX_LENGTH) {
                delete[] result;
                throw OverflowException("Input string exceeds maximum allowed length");
            }
            
            capacity *= 2;
            auto newBuffer = new char[capacity];
            if (!newBuffer) {
                delete[] result;
                throw MemoryAllocationException("Failed to reallocate buffer during input");
            }
            for (int i = 0; i < length; i++) {
                newBuffer[i] = result[i];
            }
            delete[] result;
            result = newBuffer;
        }
        result[length++] = ch;
    }
    result[length] = '\0';

    if (length > String::MAX_LENGTH) {
        delete[] result;
        throw OverflowException("Input string exceeds maximum allowed length");
    }

    delete[] string.data;
    string.length = length;
    string.data = new char[length + 1];
    if (!string.data) {
        delete[] result;
        throw MemoryAllocationException("Failed to allocate memory for final string");
    }
    
    for (int i = 0; i < length; i++) {
        string.data[i] = result[i];
    }
    string.data[length] = '\0';

    delete[] result;
}