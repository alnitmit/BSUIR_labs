#include "../include/Rectangle.h"
#include <iostream>
#include "../include/constants.h"

RectangleShape::RectangleShape(double w, double h) : width(w), height(h) {}

void RectangleShape::print() const {
    std::cout << "Rectangle(width=" << width << ", height=" << height << ")" << std::endl;
}

double RectangleShape::area() const {
    return width * height;
}

void RectangleShape::draw() const {
    for (int i = 0; i < (int)height; ++i) {
        for (int j = 0; j < (int)width; ++j) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}