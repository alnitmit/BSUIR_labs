#include "../include/String.h"
#include "../include/Exception.h"
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
    std::cout << "8. Demonstrate exception hierarchy\n";
    std::cout << "9. Demonstrate exception order importance\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void demonstrateExceptionHierarchy() {
    std::cout << "\n=== Demonstrating Exception Hierarchy ===\n";
    
    try {
        throw MemoryAllocationException("Custom memory allocation error");
    } catch (const MemoryAllocationException& e) {
        std::cout << "Caught MemoryAllocationException: " << e.what() << std::endl;
    } catch (const MemoryException& e) {
        std::cout << "Caught MemoryException: " << e.what() << std::endl;
    } catch (const Exception& e) {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }
    
    try {
        throw IndexOutOfBoundsException("Custom index error");
    } catch (const RangeException& e) {
        std::cout << "Caught RangeException: " << e.what() << std::endl;
    } catch (const Exception& e) {
        std::cout << "Caught Exception: " << e.what() << std::endl;
    }
}

void demonstrateExceptionOrder() {
    std::cout << "\n=== Demonstrating Exception Order Importance ===\n";
    
    std::cout << "Correct order:\n";
    try {
        throw IndexOutOfBoundsException("Index 100 out of bounds");
    } 
    catch (const IndexOutOfBoundsException& e) {
        std::cout << "  Caught IndexOutOfBoundsException: " << e.what() << std::endl;
    }
    catch (const RangeException& e) {
        std::cout << "  Caught RangeException: " << e.what() << std::endl;
    }
    catch (const Exception& e) {
        std::cout << "  Caught Exception: " << e.what() << std::endl;
    }
    
    std::cout << "Incorrect order:\n";
    try {
        throw IndexOutOfBoundsException("Index 100 out of bounds");
    } 
    catch (const Exception& e) {
        std::cout << "  Caught Exception: " << e.what() << std::endl;
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
            switch (choice) {
            case 1: {
                input(currentString);
                std::cout << "String input successful!" << std::endl;
                break;
            }
            case 2: {
                std::cout << "First string: ";
                print(currentString);
                break;
            }
            case 3: {
                std::cout << "Second string: ";
                print(secondString);
                break;
            }
            case 4: {
                secondString = currentString;
                std::cout << "String copied successfully!" << std::endl;
                break;
            }
            case 5: {
                std::cout << "Concatenating strings..." << std::endl;
                currentString += secondString;
                std::cout << "Result: ";
                print(currentString);
                break;
            }
            case 6: {
                std::cout << "Comparing strings: ";
                if (currentString == secondString) {
                    std::cout << "Strings are equal.\n";
                } else {
                    std::cout << "Strings are not equal.\n";
                }
                break;
            }
            case 7: {
                std::cout << "Enter index to access: ";
                int index;
                if (std::cin >> index) {
                    try {
                        char ch = currentString[index];
                        std::cout << "Character at index " << index << ": '" << ch << "'\n";
                    } catch (const IndexOutOfBoundsException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                }
                clearInputBuffer();
                break;
            }
            case 8: {
                demonstrateExceptionHierarchy();
                break;
            }
            case 9: {
                demonstrateExceptionOrder();
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
        } catch (const MemoryAllocationException& e) {
            std::cout << "Memory Allocation Error: " << e.what() << std::endl;
        } catch (const OverflowException& e) {
            std::cout << "Overflow Error: " << e.what() << std::endl;
        } catch (const IndexOutOfBoundsException& e) {
            std::cout << "Index Error: " << e.what() << std::endl;
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