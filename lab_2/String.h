#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
private:
  char *data;
  int length;

  void freeMemory() {
    delete[] data;
    data = nullptr;
    length = 0;
  }

  void copyFrom(const char *str, int len) {
    data = new char[len + 1];
    for (int i = 0; i < len; i++) {
      data[i] = str[i];
    }
    data[len] = '\0';
    length = len;
  }

public:
  String() : data(nullptr), length(0) {
    data = new char[1];
    data[0] = '\0';
  }

  String(const String &other) {
    if (other.data) {
      copyFrom(other.data, other.length);
    } else {
      data = new char[1];
      data[0] = '\0';
      length = 0;
    }
  }

  ~String() { freeMemory(); }

  String &operator=(const String &other) {
    if (this != &other) {
      freeMemory();
      if (other.data) {
        copyFrom(other.data, other.length);
      }
    }
    return *this;
  }

  String &operator+=(const String &other) {
    if (other.data && other.length > 0) {
      int newLength = length + other.length;
      char *newData = new char[newLength + 1];

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