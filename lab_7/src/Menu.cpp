#include <iostream>
#include <fstream>
#include "Menu.h"
#include "FileOperations.h"

void displayMenu() {
    std::cout << "\n=== WAREHOUSE MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Add new product\n";
    std::cout << "2. View all products\n";
    std::cout << "3. Find product by ID\n";
    std::cout << "4. Update product information\n";
    std::cout << "5. Delete product\n";
    std::cout << "6. Show total inventory value\n";
    std::cout << "7. Exit\n";
    std::cout << "Choose an option: ";
}

void handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            displayAllProducts();
            break;
        case 3:
            findProduct();
            break;
        case 4:
            updateProduct();
            break;
        case 5:
            deleteProduct();
            break;
        case 6:
            showTotalInventoryValue();
            break;
        case 7:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}