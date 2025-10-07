#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "TwoDShape.h"
#include <iostream>
#include "../include/constants.h"

class Triangle : public TwoDShape {
private:
    double base;
    double height;
    
public:
    Triangle(double b, double h);
    void print() const override;
    double area() const override;
    void draw() const override;
};

#endif