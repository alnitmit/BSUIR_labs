#include "../include/item.h"

int main() {
    initializeFile();
    int choice = 0;

    do {
        std::cout << "\n=== Inventory Management System ===\n";
        std::cout << "1. Add item\n";
        std::cout << "2. Display all items\n";
        std::cout << "3. Delete item\n";
        std::cout << "4. Update item\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!getValidInput("", choice)) continue;

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayAllItems(); break;
            case 3: deleteItem(); break;
            case 4: updateItem(); break;
            case 5: std::cout << "Exiting program...\n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}