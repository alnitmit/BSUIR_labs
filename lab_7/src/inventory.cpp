#include "../include/item.h"

const std::string FILENAME = "inventory.dat";

void writeItem(std::ostream& os, const Item& item) {
    os.write(reinterpret_cast<const char*>(&item), sizeof(Item));
}

bool readItem(std::istream& is, Item& item) {
    is.read(reinterpret_cast<char*>(&item), sizeof(Item));
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
    std::string name;
    std::getline(std::cin, name);
    
    for (int i = 0; i < 49 && i < name.length(); i++) {
        newItem.name[i] = name[i];
    }
    newItem.name[49] = '\0';

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
    }
    return false;
}

bool updateItemInFile(long position, const Item& item) {
    std::fstream file(FILENAME, std::ios::binary | std::ios::in | std::ios::out);
    if (!file) {
        return false;
    }

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
        std::string name;
        std::getline(std::cin, name);
        
        for (int i = 0; i < 49 && i < name.length(); i++) {
            foundItem.name[i] = name[i];
        }
        foundItem.name[49] = '\0';
        
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
