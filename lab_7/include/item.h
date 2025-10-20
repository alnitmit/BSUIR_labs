#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

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

#endif