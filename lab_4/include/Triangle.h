#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public TwoDShape {
private:
    double base, height;
    
public:
    Triangle(double b, double h);
    void print() const override;
    double area() const override;
    void draw() const override;
};

#endif