#include "../include/String.h"
#include <iostream>

void clearInputBuffer() {
  std::cin.clear();
  std::cin.ignore(10000, '\n');
}

void displayMenu() {
  std::cout << "\n   STRING CLASS DEMONSTRATION    \n";
  std::cout << "1. Input first string\n";
  std::cout << "2. Display first string\n";
  std::cout << "3. Display second string\n";
  std::cout << "4. Copy first string to second\n";
  std::cout << "5. Concatenate strings\n";
  std::cout << "6. Compare strings\n";
  std::cout << "0. Exit\n";
  std::cout << "Choose an option: ";
}

void runStringDemoProgram() {
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
      return;
    }
    default: {
      std::cout << "Invalid choice. Try again!!!!\n";
      break;
    }
    }
  }
}

int main() {
  runStringDemoProgram();
  return 0;
}