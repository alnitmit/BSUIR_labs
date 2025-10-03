#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

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