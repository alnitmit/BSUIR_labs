#include <iostream>
#include <fstream>
#include "../include/Menu.h"
#include "../include/Product.h"

int main() {
    int choice;
    
    std::fstream file(FILENAME, std::ios::binary | std::ios::app);
    file.close();

    std::cout << "Welcome to the Metal Products Warehouse Management System!\n";

    do {
        displayMenu();
        std::cin >> choice;
        handleMenuChoice(choice);
    } while (choice != 7);

    return 0;
}