#ifndef PRODUCT_H
#define PRODUCT_H

const int NAME_LENGTH = 50;
const char* FILENAME = "inventory.dat";

struct Product {
    int id;
    char name[NAME_LENGTH];
    int quantity;
    double price;
    bool active;

    Product();
};

void copyString(char* dest, const char* src, int maxLength);
int stringLength(const char* str);

#endif