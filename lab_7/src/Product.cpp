#include "Product.h"

Product::Product() : id(0), quantity(0), price(0.0), active(true) {
    for (int i = 0; i < NAME_LENGTH; i++) {
        name[i] = '\0';
    }
}

void copyString(char* dest, const char* src, int maxLength) {
    int i = 0;
    while (i < maxLength - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

const char* FILENAME = "inventory.dat";