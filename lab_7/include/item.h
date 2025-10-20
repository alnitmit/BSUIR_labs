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

extern const char* FILENAME;
extern const int NAME_SIZE;

void initializeFile();
void addItem();
void displayAllItems();
void deleteItem();
void updateItem();

#endif