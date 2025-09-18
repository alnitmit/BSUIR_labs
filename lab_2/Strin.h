#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <span>

class String {
private:
  char *data;
  int length = 0;

  void freeMemory() {
    delete[] data;
    data = nullptr;
    length = 0;
  }

  void copyFrom(std::span<const char> str) {
    length = str.size();
    data = new char[length + 1];
    for (int i = 0; i < length; i++) {
      data[i] = str[i];
    }
    data[length] = '\0';
  }

public:
  String() : data(new char[1]) { data[0] = '\0'; }

  String(const String &other) : data(nullptr) {
    if (other.data) {
      copyFrom(std::span<const char>(other.data, other.length));
    } else {
      data = new char[1];
      data[0] = '\0';
    }
  }

  ~String() { freeMemory(); }

  String &operator=(const String &other) {
    if (this != &other) {
      freeMemory();
      if (other.data) {
        copyFrom(std::span<const char>(other.data, other.length));
      } else {
        data = new char[1];
        data[0] = '\0';
        length = 0;
      }
    }
    return *this;
  }

  String &operator+=(const String &other) {
    if (other.data && other.length > 0) {
      int newLength = length + other.length;
      auto newData = new char[newLength + 1];

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

  bool operator==(const String &other) const {
    if (this == &other)
      return true;
    if (length != other.length)
      return false;
    for (int i = 0; i < length; i++) {
      if (data[i] != other.data[i])
        return false;
    }
    return true;
  }

  friend void print(const String &);
  friend void input(String &);
};

#endif