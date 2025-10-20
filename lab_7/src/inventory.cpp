#include "item.h"
#include <fstream>
#include <limits>

const char* FILENAME = "inventory.dat";
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
    if (std::fstream file(FILENAME, std::ios::binary | std::ios::out | std::ios::in); !file) {
        file.open(FILENAME, std::ios::binary | std::ios::out);
    }
}

void addItem() {
    Item newItem{};
    
    if (!getValidInput("Enter item ID: ", newItem.id)) return;

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
    std::cin.getline(newItem.name, NAME_SIZE);
    
    if (!getValidInput("Enter quantity: ", newItem.quantity)) return;
    if (!getValidInput("Enter cost: ", newItem.cost)) return;

    newItem.active = true;

    if (std::ofstream outFile(FILENAME, std::ios::binary | std::ios::app); outFile) {
        outFile.write(reinterpret_cast<const char*>(&newItem), sizeof(Item));
        std::cout << "Item added successfully.\n";
    } else {
        std::cout << "Error opening file for writing.\n";
    }
}

void displayAllItems() {
    if (std::ifstream file(FILENAME, std::ios::binary); !file) {
        std::cout << "No items found.\n";
        return;
    }

    std::ifstream file(FILENAME, std::ios::binary);
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
    if (!getValidInput("Enter item ID to delete: ", idToDelete)) return;

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
    if (!getValidInput("Enter item ID to update: ", idToUpdate)) return;

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
            std::cin.getline(temp.name, NAME_SIZE);
            
            if (!getValidInput("Enter new quantity: ", temp.quantity)) return;
            if (!getValidInput("Enter new cost: ", temp.cost)) return;

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