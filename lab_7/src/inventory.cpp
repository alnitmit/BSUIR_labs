#include "../include/item.h"
#include <fstream>
#include <limits>

const std::string FILENAME = "inventory.dat";
const int NAME_SIZE = 50;

bool getValidInput(const std::string& prompt, int& value) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return false;
    }
    return true;
}

bool getValidInput(const std::string& prompt, double& value) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Operation cancelled.\n";
        return false;
    }
    return true;
}

void initializeFile() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::out | std::ios::in);
    if (!file) {
        file.open(FILENAME, std::ios::binary | std::ios::out);
    }
}

void addItem() {
    Item newItem{};
    
    if (!getValidInput("Enter item ID: ", newItem.id)) return;

    std::ifstream inFile(FILENAME, std::ios::binary);
    if (inFile) {
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
    
    if (!getValidInput("Enter quantity: ", newItem.quantity)) return;
    if (!getValidInput("Enter cost: ", newItem.cost)) return;

    newItem.active = true;

    std::ofstream outFile(FILENAME, std::ios::binary | std::ios::app);
    outFile.write(reinterpret_cast<const char*>(&newItem), sizeof(Item));
    std::cout << "Item added successfully.\n";
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

bool findItem(int id, Item& foundItem, long& position) {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        return false;
    }

    position = 0;
    Item temp{};
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Item))) {
        if (temp.active && temp.id == id) {
            foundItem = temp;
            return true;
        }
        position += sizeof(Item);
    }
    return false;
}

bool updateItemInFile(long position, const Item& item) {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        return false;
    }

    file.seekp(position);
    file.write(reinterpret_cast<const char*>(&item), sizeof(Item));
    return true;
}

void deleteItem() {
    int idToDelete;
    if (!getValidInput("Enter item ID to delete: ", idToDelete)) return;

    Item foundItem{};
    long position;
    if (findItem(idToDelete, foundItem, position)) {
        foundItem.active = false;
        if (updateItemInFile(position, foundItem)) {
            std::cout << "Item deleted successfully.\n";
        } else {
            std::cout << "Error updating file.\n";
        }
    } else {
        std::cout << "Item not found.\n";
    }
}

void updateItem() {
    int idToUpdate;
    if (!getValidInput("Enter item ID to update: ", idToUpdate)) return;

    Item foundItem{};
    long position;
    if (findItem(idToUpdate, foundItem, position)) {
        std::cout << "Enter new name: ";
        std::cin.ignore();
        std::getline(std::cin, foundItem.name);
        
        if (!getValidInput("Enter new quantity: ", foundItem.quantity)) return;
        if (!getValidInput("Enter new cost: ", foundItem.cost)) return;

        if (updateItemInFile(position, foundItem)) {
            std::cout << "Item updated successfully.\n";
        } else {
            std::cout << "Error updating file.\n";
        }
    } else {
        std::cout << "Item not found.\n";
    }
}