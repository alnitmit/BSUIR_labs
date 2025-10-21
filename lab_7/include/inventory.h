#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <string>

class Inventory {
private:
    std::string filename;
    std::string tempFilename;
    
    bool getValidInput(const std::string& prompt, int& value);
    bool getValidInput(const std::string& prompt, double& value);
    bool itemExists(int id);
    bool findItem(int id, Item& foundItem, long& position);
    bool updateItemInFile(long position, const Item& item);
    
public:
    Inventory(const std::string& filename = "inventory.dat", 
              const std::string& tempFilename = "temp_inventory.dat");
    
    void initializeFile();
    void addItem();
    void displayAllItems();
    void deleteItem();
    void updateItem();
};

#endif