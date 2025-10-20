#include "../include/item.h"
#include <fstream>
#include <limits>

const std::string FILENAME = "inventory.dat";
const int NAME_SIZE = 50;

template<typename T>
void writeAsBytes(std::ostream& os, const T& obj) {
    os.write(reinterpret_cast<const char*>(&obj), sizeof(obj));
}

template<typename T>
void readAsBytes(std::istream& is, T& obj) {
    is.read(reinterpret_cast<char*>(&obj), sizeof(obj));
}

void writeString(std::ostream& os, const std::string& str) {
    size_t size = str.size();
    writeAsBytes(os, size);
    os.write(str.c_str(), static_cast<std::streamsize>(size));
}

void readString(std::istream& is, std::string& str) {
    size_t size;
    readAsBytes(is, size);
    str.resize(size);
    is.read(&str[0], static_cast<std::streamsize>(size));
}

void writeItem(std::ostream& os, const Item& item) {
    writeAsBytes(os, item.id);
    writeString(os, item.name);
    writeAsBytes(os, item.quantity);
    writeAsBytes(os, item.cost);
    writeAsBytes(os, item.active);
}

bool readItem(std::istream& is, Item& item) {
    readAsBytes(is, item.id);
    readString(is, item.name);
    readAsBytes(is, item.quantity);
    readAsBytes(is, item.cost);
    readAsBytes(is, item.active);
    return !is.fail();
}

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
        while (readItem(inFile, temp)) {
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

    if (std::ofstream outFile(FILENAME, std::ios::binary | std::ios::app); outFile) {
        writeItem(outFile, newItem);
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
    while (readItem(file, temp)) {
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
    if (std::ifstream file(FILENAME, std::ios::binary); !file) {
        return false;
    }

    std::ifstream file(FILENAME, std::ios::binary);
    position = 0;
    Item temp{};
    while (readItem(file, temp)) {
        if (temp.active && temp.id == id) {
            foundItem = temp;
            return true;
        }
        position = file.tellg();
    }
    return false;
}

bool updateItemInFile(long position, const Item& item) {
    if (std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out); !file) {
        return false;
    }

    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(position);
    writeItem(file, item);
    return !file.fail();
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