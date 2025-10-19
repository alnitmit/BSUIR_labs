#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstddef>
#include "../include/FileOperations.h"
#include "../include/Product.h"

bool idExists(std::fstream& file, int id) {
    Product product;
    file.seekg(0, std::ios::beg);
    
    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active && product.id == id) {
            return true;
        }
    }
    return false;
}

void addProduct() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
    if (!file) {
        std::cerr << "Error opening file!\n";
        return;
    }

    Product product;
    
    std::cout << "Enter product ID: ";
    std::cin >> product.id;
    
    if (idExists(file, product.id)) {
        std::cout << "Error: Product with this ID already exists!\n";
        return;
    }

    std::cin.ignore();
    std::cout << "Enter product name: ";
    
    std::string tempName;
    std::getline(std::cin, tempName);
    
    // Копируем строку в фиксированный массив
    std::strncpy(product.name.data(), tempName.c_str(), NAME_LENGTH - 1);
    product.name[NAME_LENGTH - 1] = '\0'; // Гарантируем нулевое завершение
    
    std::cout << "Enter quantity: ";
    std::cin >> product.quantity;
    
    std::cout << "Enter price per unit: ";
    std::cin >> product.price;

    product.active = true;

    file.write(reinterpret_cast<const std::byte*>(&product), sizeof(Product));
    file.close();
    
    std::cout << "Product added successfully!\n";
}

void displayAllProducts() {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        std::cerr << "File does not exist or cannot be opened!\n";
        return;
    }

    Product product;
    bool found = false;
    
    std::cout << "\nID\tName\t\t\tQuantity\tPrice\tTotal Value\n";
    std::cout << "------------------------------------------------------------------------\n";

    double totalInventoryValue = 0.0;

    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active) {
            found = true;
            double totalValue = product.quantity * product.price;
            totalInventoryValue += totalValue;
            
            std::cout << product.id << "\t" 
                      << product.name.data() << "\t\t"
                      << product.quantity << "\t\t"
                      << product.price << "\t"
                      << totalValue << "\n";
        }
    }

    if (!found) {
        std::cout << "No products in inventory.\n";
    } else {
        std::cout << "------------------------------------------------------------------------\n";
        std::cout << "Total inventory value: " << totalInventoryValue << "\n";
    }

    file.close();
}

void findProduct() {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        std::cerr << "File does not exist!\n";
        return;
    }

    int searchId;
    std::cout << "Enter ID to search: ";
    std::cin >> searchId;

    Product product;
    bool found = false;

    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active && product.id == searchId) {
            found = true;
            std::cout << "\nProduct found:\n";
            std::cout << "ID: " << product.id << "\n";
            std::cout << "Name: " << product.name.data() << "\n";
            std::cout << "Quantity: " << product.quantity << "\n";
            std::cout << "Price: " << product.price << "\n";
            std::cout << "Total value: " << (product.quantity * product.price) << "\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Product with ID " << searchId << " not found.\n";
    }

    file.close();
}

void updateProduct() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "File does not exist!\n";
        return;
    }

    int updateId;
    std::cout << "Enter product ID to update: ";
    std::cin >> updateId;

    Product product;
    bool found = false;
    std::streampos position;

    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active && product.id == updateId) {
            found = true;
            position = file.tellg() - static_cast<std::streampos>(sizeof(Product));
            break;
        }
    }

    if (!found) {
        std::cout << "Product with ID " << updateId << " not found.\n";
        file.close();
        return;
    }

    std::cout << "Current data:\n";
    std::cout << "Name: " << product.name.data() << "\n";
    std::cout << "Quantity: " << product.quantity << "\n";
    std::cout << "Price: " << product.price << "\n";

    std::cin.ignore();
    std::cout << "Enter new name (or press Enter to keep current): ";
    
    std::string newName;
    std::getline(std::cin, newName);
    
    if (!newName.empty()) {
        std::strncpy(product.name.data(), newName.c_str(), NAME_LENGTH - 1);
        product.name[NAME_LENGTH - 1] = '\0';
    }

    std::cout << "Enter new quantity (or -1 to keep current): ";
    int newQuantity;
    std::cin >> newQuantity;
    if (newQuantity >= 0) {
        product.quantity = newQuantity;
    }

    std::cout << "Enter new price (or -1 to keep current): ";
    double newPrice;
    std::cin >> newPrice;
    if (newPrice >= 0) {
        product.price = newPrice;
    }

    file.seekp(position);
    file.write(reinterpret_cast<const std::byte*>(&product), sizeof(Product));
    file.close();

    std::cout << "Product information updated!\n";
}

void deleteProduct() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cerr << "File does not exist!\n";
        return;
    }

    int deleteId;
    std::cout << "Enter product ID to delete: ";
    std::cin >> deleteId;

    Product product;
    bool found = false;
    std::streampos position;

    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active && product.id == deleteId) {
            found = true;
            position = file.tellg() - static_cast<std::streampos>(sizeof(Product));
            break;
        }
    }

    if (!found) {
        std::cout << "Product with ID " << deleteId << " not found.\n";
        file.close();
        return;
    }

    product.active = false;
    file.seekp(position);
    file.write(reinterpret_cast<const std::byte*>(&product), sizeof(Product));
    file.close();

    std::cout << "Product deleted!\n";
}

void showTotalInventoryValue() {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        std::cerr << "File does not exist!\n";
        return;
    }

    Product product;
    double totalValue = 0.0;
    int totalItems = 0;

    while (file.read(reinterpret_cast<std::byte*>(&product), sizeof(Product))) {
        if (product.active) {
            totalValue += product.quantity * product.price;
            totalItems += product.quantity;
        }
    }

    std::cout << "\nInventory statistics:\n";
    std::cout << "Total value: " << totalValue << "\n";
    std::cout << "Total items: " << totalItems << "\n";

    file.close();
}