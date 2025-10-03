#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public ThreeDShape {
private:
    double radius, height;
    
public:
    Cylinder(double r, double h);
    void print() const override;
    double area() const override;
    double volume() const override;
    void draw() const override;
};

#endif