#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "Product.h"
#include <fstream>

bool idExists(std::fstream& file, int id);
void addProduct();
void displayAllProducts();
void findProduct();
void updateProduct();
void deleteProduct();
void showTotalInventoryValue();

#endif