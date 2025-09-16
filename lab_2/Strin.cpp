  #include "Strin.h"
  #include <cctype>
  #include <iostream>
  #include <limits>

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

  void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  void displayMenu() {
    std::cout << "\n=== STRING CLASS DEMONSTRATION ===\n";
    std::cout << "1. Input first string\n";
    std::cout << "2. Display first string\n";
    std::cout << "3. Display second string\n";
    std::cout << "4. Copy first string to second\n";
    std::cout << "5. Concatenate strings\n";
    std::cout << "6. Compare strings\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
  }

  int main() {
    String currentString;
    String secondString;
    int choice;

    while (true) {
      displayMenu();
      if (!(std::cin >> choice)) {
        clearInputBuffer();
        std::cout << "Invalid input! Please enter a number.\n";
        continue;
      }

      clearInputBuffer();

      switch (choice) {
      case 1: {
        input(currentString);
        break;
      }
      case 2: {
        std::cout << "First string: " << std::endl;
        print(currentString);
        break;
      }
      case 3: {
        std::cout << "Second string: " << std::endl;
        print(secondString);
        break;
      }
      case 4: {
        secondString = currentString;
        std::cout << "String copied " << std::endl;
        break;
      }
      case 5: {
        std::cout << "Concatenate: " << std::endl;
        currentString += secondString;
        std::cout << "Result: " << std::endl;
        print(currentString);
        break;
      }
      case 6: {
        std::cout << "Compare: " << std::endl;
        if (currentString == secondString) {
          std::cout << "Strings are equal.\n";
        } else {
          std::cout << "Strings are not equal.\n";
        }
        break;
      }
      case 0: {
        std::cout << "Exiting program.\n";
        return 0;
      }
      default: {
        std::cout << "Invalid choice. Try again!!!!\n";
        break;
      }
      }
    }
    return 0;
  }