
#include "../include/item.h"
#include <fstream>
#include <limits>
#include <cstring>
#include <array>

const std::string FILENAME = "inventory.dat";
const int NAME_SIZE = 50;

template<typename T>
void writeAsBytes(std::ostream& os, const T& obj) {
    std::array<std::byte, sizeof(obj)> buffer;
    std::memcpy(buffer.data(), &obj, sizeof(obj));
    os.write(reinterpret_cast<const char*>(buffer.data()), sizeof(obj));
}

template<typename T>
void readAsBytes(std::istream& is, T& obj) {
    std::array<std::byte, sizeof(obj)> buffer;
    is.read(reinterpret_cast<char*>(buffer.data()), sizeof(obj));
    if (is.gcount() == sizeof(obj)) {
        std::memcpy(&obj, buffer.data(), sizeof(obj));
    } else {
        is.setstate(std::ios::failbit);
    }
}

void writeString(std::ostream& os, const std::string& str) {
    size_t size = str.size();
    writeAsBytes(os, size);
    if (size > 0) {
        os.write(str.c_str(), static_cast<std::streamsize>(size));
    }
}

bool readString(std::istream& is, std::string& str) {
    size_t size = 0; // Инициализируем нулем
    readAsBytes(is, size);
    
    // Проверка на корректный размер строки
    if (is.fail() || size > 1000000) { // Ограничим максимальный размер для безопасности
        is.setstate(std::ios::failbit);
        return false;
    }
    
    if (size > 0) {
        str.resize(size);
        is.read(str.data(), static_cast<std::streamsize>(size));
        if (is.gcount() != static_cast<std::streamsize>(size)) {
            is.setstate(std::ios::failbit);
            return false;
        }
    } else {
        str.clear();
    }
    return true;
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
    if (!readString(is, item.name)) return false;
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

void initializeFile() {
    std::fstream file(FILENAME, std::ios::binary | std::ios::out | std::ios::in);
    if (!file) {
        file.open(FILENAME, std::ios::binary | std::ios::out);
        file.close();
    }
}

void addItem() {
    Item newItem{};
    
    if (!getValidInput("Enter item ID: ", newItem.id)) return;

    std::ifstream inFile(FILENAME, std::ios::binary);
    if (inFile) {
        Item temp{};
        while (readItem(inFile, temp)) {
            if (temp.active && temp.id == newItem.id) {
                std::cout << "Item with this ID already exists.\n";
                return;
            }
        }
    }
    inFile.close();

    std::cout << "Enter item name: ";
    std::getline(std::cin, newItem.name);
    
    if (!getValidInput("Enter quantity: ", newItem.quantity)) return;
    if (!getValidInput("Enter cost: ", newItem.cost)) return;

    newItem.active = true;

    std::ofstream outFile(FILENAME, std::ios::binary | std::ios::app);
    if (outFile) {
        writeItem(outFile, newItem);
        std::cout << "Item added successfully.\n";
    } else {
        std::cout << "Error opening file for writing.\n";
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
    
    // Явно сбрасываем состояние потока
    file.clear();
}

bool findItem(int id, Item& foundItem, long& position) {
    std::ifstream file(FILENAME, std::ios::binary);
    if (!file) {
        return false;
    }

    position = 0;
    Item temp{};
    while (readItem(file, temp)) {
        if (temp.active && temp.id == id) {
            foundItem = temp;
            return true;
        }
        position = file.tellg();
        if (position == -1) break; // Если достигнут конец файла
    }
    return false;
}

bool updateItemInFile(long position, const Item& item) {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        return false;
    }

    file.seekp(position);
    if (file.fail()) return false;
    
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