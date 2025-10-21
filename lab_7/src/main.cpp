#include "../include/inventory.h"
#include <iostream>
#include <limits>

int main() {
    Inventory inventory;
    int choice = 0;

    do {
        std::cout << "\n\tInventory Management System\n";
        std::cout << "1. Add item\n";
        std::cout << "2. Display all items\n";
        std::cout << "3. Delete item\n";
        std::cout << "4. Update item\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: inventory.addItem(); break;
            case 2: inventory.displayAllItems(); break;
            case 3: inventory.deleteItem(); break;
            case 4: inventory.updateItem(); break;
            case 5: std::cout << "Exiting program.\n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}