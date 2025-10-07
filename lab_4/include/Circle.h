#ifndef CIRCLE_H
#define CIRCLE_H

#include "TwoDShape.h"
#include <iostream>
#include "../include/constants.h"

class Circle : public TwoDShape {
private:
  double radius;

public:
  explicit Circle(double r);
  void print() const override;
  double area() const override;
  void draw() const override;
};

#endif