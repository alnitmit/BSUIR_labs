#include "../include/Triangle.h"

Triangle::Triangle(double b, double h) : base(b), height(h) {}

void Triangle::print() const {
    std::cout << "Triangle(base=" << base << ", height=" << height << ")" << std::endl;
}

double Triangle::area() const {
    return 0.5 * base * height;
}

void Triangle::draw() const {
    for (int i = 1; i <= (int)height; ++i) {
        int stars = (i * (int)base) / (int)height;
        for (int j = 0; j < stars; ++j) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
}