#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "TwoDShape.h"
#include <iostream>

class RectangleShape : public TwoDShape {
private:
    double width;
    double height;

public:
    RectangleShape(double w, double h);
    void print() const override;
    double area() const override;
    void draw() const override;
};

#endif