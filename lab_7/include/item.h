#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <cstddef>

struct Item {
    int id;
    std::string name;
    int quantity;
    double cost;
    bool active;
};

extern const std::string FILENAME;
extern const int NAME_SIZE;

void initializeFile();
void addItem();
void displayAllItems();
void deleteItem();
void updateItem();
bool getValidInput(const std::string& prompt, int& value);
bool getValidInput(const std::string& prompt, double& value);
bool findItem(int id, Item& foundItem, long& position);
bool updateItemInFile(long position, const Item& item);
void writeItem(std::ostream& os, const Item& item);
bool readItem(std::istream& is, Item& item);

#endif