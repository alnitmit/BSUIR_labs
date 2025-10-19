#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

constexpr int NAME_LENGTH = 50;
extern const std::string FILENAME;

struct Product {
    int id = 0;
    std::string name;
    int quantity = 0;
    double price = 0.0;
    bool active = true;

    Product() = default;
};

#endif