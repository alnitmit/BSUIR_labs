#include "../include/String.h"
#include <iostream>
#include <span>  

void String::freeMemory() {
  delete[] data;
  data = nullptr;
  length = 0;
}

void String::copyFrom(std::span<const char> str) {
  length = str.size();
  data = new char[length + 1];
  for (int i = 0; i < length; i++) {
    data[i] = str[i];
  }
  data[length] = '\0';
}

String::String() : data(new char[1]) { data[0] = '\0'; }

String::String(const String &other) : data(nullptr) {
  if (other.data) {
    copyFrom(std::span<const char>(other.data, other.length));
  } else {
    data = new char[1];
    data[0] = '\0';
  }
}

String::~String() { freeMemory(); }

String &String::operator=(const String &other) {
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

String &String::operator+=(const String &other) {
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

bool String::operator==(const String &other) const {
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

  std::cout << "Enter string:" << std::endl;
  while (std::cin.get(ch) && ch != '\n') {
    if (length + 1 >= capacity) {
      capacity *= 2;
      auto newBuffer = new char[capacity];
      for (int i = 0; i < length; i++) {
        newBuffer[i] = result[i];
      }
      delete[] result;
      result = newBuffer;
    }
    result[length++] = ch;
  }
  result[length] = '\0';

  delete[] string.data;
  string.length = length;
  string.data = new char[length + 1];
  for (int i = 0; i < length; i++) {
    string.data[i] = result[i];
  }
  string.data[length] = '\0';

  delete[] result;
}