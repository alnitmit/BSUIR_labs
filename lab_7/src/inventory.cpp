#include "../include/item.h"
#include <fstream>
#include <limits>

const std::string FILENAME = "inventory.dat";
const int NAME_SIZE = 50;

void initializeFile() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::out | std::ios::in);
    if (!file) {
        file.open(FILENAME, std::ios::binary | std::ios::out);
        file.close();
    }
}

void addItem() {
    Item newItem{};
    std::cout << "Enter item ID: ";
    std::cin >> newItem.id;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return;
    }

    if (std::ifstream inFile(FILENAME, std::ios::binary); inFile) {
        Item temp{};
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
            if (temp.active && temp.id == newItem.id) {
                std::cout << "Item with this ID already exists.\n";
                return;
            }
        }
    }

    std::cout << "Enter item name: ";
    std::cin.ignore();
    std::getline(std::cin, newItem.name);
    
    std::cout << "Enter quantity: ";
    std::cin >> newItem.quantity;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return;
    }

    std::cout << "Enter cost: ";
    std::cin >> newItem.cost;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return;
    }

    newItem.active = true;

    if (std::ofstream outFile(FILENAME, std::ios::binary | std::ios::app); outFile) {
        outFile.write(reinterpret_cast<const char*>(&newItem), sizeof(Item));
        std::cout << "Item added successfully.\n";
    }
}

void displayAllItems() {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        std::cout << "No items found.\n";
        return;
    }

    Item temp{};
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
        if (temp.active) {
            std::cout << "ID: " << temp.id << ", Name: " << temp.name
                      << ", Quantity: " << temp.quantity << ", Cost: " << temp.cost << '\n';
            found = true;
        }
    }

    if (!found) {
        std::cout << "No active items found.\n";
    }
}

void deleteItem() {
    int idToDelete;
    std::cout << "Enter item ID to delete: ";
    std::cin >> idToDelete;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return;
    }

    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    Item temp{};
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
        if (temp.active && temp.id == idToDelete) {
            temp.active = false;
            file.seekp(-static_cast<int>(sizeof(Item)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&temp), sizeof(Item));
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Item deleted successfully.\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

void updateItem() {
    int idToUpdate;
    std::cout << "Enter item ID to update: ";
    std::cin >> idToUpdate;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return;
    }

    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "Error opening file.\n";
        return;
    }

    Item temp{};
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
        if (temp.active && temp.id == idToUpdate) {
            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::getline(std::cin, temp.name);
            
            std::cout << "Enter new quantity: ";
            std::cin >> temp.quantity;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Operation cancelled.\n";
                return;
            }
            
            std::cout << "Enter new cost: ";
            std::cin >> temp.cost;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Operation cancelled.\n";
                return;
            }

            file.seekp(-static_cast<int>(sizeof(Item)), std::ios::cur);
            file.write(reinterpret_cast<const char*>(&temp), sizeof(Item));
            found = true;
            break;
        }
    }

    if (found) {
        std::cout << "Item updated successfully.\n";
    } else {
        std::cout << "Item not found.\n";
    }
}