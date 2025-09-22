#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <span>

class String {
private:
  char *data;
  int length = 0;

  void freeMemory();
  void copyFrom(std::span<const char> str);

public:
  String();
  String(const String &other);
  ~String();

  String &operator=(const String &other);
  String &operator+=(const String &other);
  bool operator==(const String &other) const;

  friend void print(const String &);
  friend void input(String &);
};

#endif