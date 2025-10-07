#include "../include/Sphere.h"
#include "../include/constants.h"

Sphere::Sphere(double r) : radius(r) {}

void Sphere::print() const {
    std::cout << "Sphere(radius=" << radius << ")" << std::endl;
}

double Sphere::area() const {
    return 4 * constants::PI * radius * radius;
}

double Sphere::volume() const {
    return (4.0 / 3.0) * constants::PI * radius * radius * radius;
}

void Sphere::draw() const {
    std::cout << "   *****   " << std::endl;
    std::cout << " *       * " << std::endl;
    std::cout << "*         *" << std::endl;
    std::cout << " *       * " << std::endl;
    std::cout << "   *****   " << std::endl;
}