#include "../include/String.h"
#include "../include/exceptions/Exception.h"
#include "../include/exceptions/MemoryAllocationException.h"
#include "../include/exceptions/IndexOutOfBoundsException.h"
#include "../include/exceptions/InvalidArgumentException.h"
#include "../include/exceptions/OverflowException.h"
#include "../include/exceptions/ArgumentException.h"
#include <iostream>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}       

void displayMenu() {
    std::cout << "\n   STRING CLASS DEMONSTRATION WITH EXCEPTIONS    \n";
    std::cout << "1. Input first string\n";
    std::cout << "2. Display first string\n";
    std::cout << "3. Display second string\n";
    std::cout << "4. Copy first string to second\n";
    std::cout << "5. Concatenate strings\n";
    std::cout << "6. Compare strings\n";
    std::cout << "7. Access character by index\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void handleInputOperation(String& currentString) {
    input(currentString);
    std::cout << "String input successful!" << std::endl;
}

void handleDisplayOperation(const String& string, const std::string& label) {
    std::cout << label << ": ";
    print(string);
}

void handleCopyOperation(String& dest, const String& src) {
    dest = src;
    std::cout << "String copied successfully!" << std::endl;
}

void handleConcatenateOperation(String& currentString, const String& secondString) {
    std::cout << "Concatenating strings..." << std::endl;
    currentString += secondString;
    std::cout << "Result: ";
    print(currentString);
}

void handleCompareOperation(const String& currentString, const String& secondString) {
    std::cout << "Comparing strings: ";
    if (currentString == secondString) {
        std::cout << "Strings are equal.\n";
    } else {
        std::cout << "Strings are not equal.\n";
    }
}

void handleAccessCharacterOperation(const String& currentString) {
    std::cout << "Enter index to access: ";
    if (int index; std::cin >> index) {
        char ch = currentString[index];
        std::cout << "Character at index " << index << ": '" << ch << "'\n";
    }
    clearInputBuffer();
}

void handleAccessCharacterSafe(const String& currentString) {
    try {
        handleAccessCharacterOperation(currentString);
    } catch (const IndexOutOfBoundsException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void processMenuChoice(int choice, String& currentString, String& secondString) {
    switch (choice) {
    case 1: {
        handleInputOperation(currentString);
        break;
    }
    case 2: {
        handleDisplayOperation(currentString, "First string");
        break;
    }
    case 3: {
        handleDisplayOperation(secondString, "Second string");
        break;
    }
    case 4: {
        handleCopyOperation(secondString, currentString);
        break;
    }
    case 5: {
        handleConcatenateOperation(currentString, secondString);
        break;
    }
    case 6: {
        handleCompareOperation(currentString, secondString);
        break;
    }
    case 7: {
        handleAccessCharacterSafe(currentString);
        break;
    }
    case 0: {
        std::cout << "Exiting program.\n";
        return;
    }
    default: {
        std::cout << "Invalid choice. Try again!\n";
        break;
    }
    }
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

        try {
            processMenuChoice(choice, currentString, secondString);
            if (choice == 0) return;
        } catch (const MemoryAllocationException& e) {
            std::cout << "Memory Allocation Error: " << e.what() << std::endl;
        } catch (const OverflowException& e) {
            std::cout << "Overflow Error: " << e.what() << std::endl;
        } catch (const IndexOutOfBoundsException& e) {
            std::cout << "Index Error: " << e.what() << std::endl;
        } catch (const ArgumentException& e) {
            std::cout << "Argument Error: " << e.what() << std::endl;
        } catch (const InvalidArgumentException& e) {
            std::cout << "Argument Error: " << e.what() << std::endl;
        } catch (const Exception& e) {
            std::cout << "General Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    runStringDemoProgram();
    return 0;
}