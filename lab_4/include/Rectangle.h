#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "TwoDShape.h"
#include <iostream>
#include "../include/constants.h"

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