#include "../include/Cube.h"
#include "../include/constants.h"

Cube::Cube(double s) : side(s) {}

void Cube::print() const {
    std::cout << "Cube(side=" << side << ")" << std::endl;
}

double Cube::area() const {
    return 6 * side * side;
}

double Cube::volume() const {
    return side * side * side;
}

void Cube::draw() const {
    std::cout << "  ******" << std::endl;
    std::cout << " *    * *" << std::endl;
    std::cout << "*    *  *" << std::endl;
    std::cout << "*****   *" << std::endl;
    std::cout << "*    *  *" << std::endl;
    std::cout << "*    * *" << std::endl;
    std::cout << "******" << std::endl;
}