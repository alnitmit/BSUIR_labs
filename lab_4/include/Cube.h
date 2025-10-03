#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public ThreeDShape {
private:
    double side;
    
public:
    explicit Cube(double s);
    void print() const override;
    double area() const override;
    double volume() const override;
    void draw() const override;
};

#endif