#include "../include/Circle.h"
#include "../include/constants.h"

Circle::Circle(double r) : radius(r) {}

void Circle::print() const {
    std::cout << "Circle(radius=" << radius << ")" << std::endl;
}

double Circle::area() const {
    return constants::PI * radius * radius;
}

void Circle::draw() const {
    std::cout << "   ***   " << std::endl;
    std::cout << " *     * " << std::endl;
    std::cout << "*       *" << std::endl;
    std::cout << " *     * " << std::endl;
    std::cout << "   ***   " << std::endl;
}