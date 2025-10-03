#include "../include/Circle.h"

Circle::Circle(double r) : radius(r) {}

void Circle::print() const {
    std::cout << "Circle(radius=" << radius << ")" << std::endl;
}

double Circle::area() const {
    return 3.14159 * radius * radius;
}

void Circle::draw() const {
    std::cout << "   ***   " << std::endl;
    std::cout << " *     * " << std::endl;
    std::cout << "*       *" << std::endl;
    std::cout << " *     * " << std::endl;
    std::cout << "   ***   " << std::endl;
}