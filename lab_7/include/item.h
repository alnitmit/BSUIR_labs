#ifndef ITEM_H
#define ITEM_H

#include <iostream>

struct Item {
    int id;
    char name[50];
    int quantity;
    double cost;
    bool active;
};

const char* FILENAME = "inventory.dat";
const int NAME_SIZE = 50;

void initializeFile();
void addItem();
void displayAllItems();
void deleteItem();
void updateItem();

#endif