#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Item {
    int id;
    char name[50];
    int quantity;
    double cost;
};

void writeItem(std::ostream& os, const Item& item);
bool readItem(std::istream& is, Item& item);
bool getValidInput(const std::string& prompt, int& value);
bool getValidInput(const std::string& prompt, double& value);
void initializeFile();
void addItem();
void displayAllItems();
bool findItem(int id, Item& foundItem, long& position);
bool updateItemInFile(long position, const Item& item);
void deleteItem();
void updateItem();

#endif