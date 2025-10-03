#include "../include/Cylinder.h"

Cylinder::Cylinder(double r, double h) : radius(r), height(h) {}

void Cylinder::print() const {
    std::cout << "Cylinder(radius=" << radius << ", height=" << height << ")" << std::endl;
}

double Cylinder::area() const {
    return 2 * 3.14159 * radius * (radius + height);
}

double Cylinder::volume() const {
    return 3.14159 * radius * radius * height;
}

void Cylinder::draw() const {
    std::cout << "   ___   " << std::endl;
    std::cout << "  /   \\  " << std::endl;
    std::cout << " |     | " << std::endl;
    std::cout << " |     | " << std::endl;
    std::cout << " |     | " << std::endl;
    std::cout << "  \\___/  " << std::endl;
}