#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Product.h"

int main() {
    int choice;
    
    std::fstream file(FILENAME, std::ios::binary | std::ios::app);
    file.close();

    std::cout << "Metal Products Warehouse Management System\n";

    do {
        displayMenu();
        std::cin >> choice;
        handleMenuChoice(choice);
    } while (choice != 7);

    return 0;
}