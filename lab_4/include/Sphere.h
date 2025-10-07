#ifndef SPHERE_H
#define SPHERE_H

#include "ThreeDShape.h"
#include <iostream>

class Sphere : public ThreeDShape {
private:
    double radius;
    
public:
    explicit Sphere(double r);
    void print() const override;
    double area() const override;
    double volume() const override;
    void draw() const override;
};

#endif