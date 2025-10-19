#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <cstddef>
#include <array>

constexpr int NAME_LENGTH = 50;
extern const std::string FILENAME;

struct Product {
    int id = 0;
    std::array<char, NAME_LENGTH> name{};
    int quantity = 0;
    double price = 0.0;
    bool active = true;

    Product() = default;
};

#endif