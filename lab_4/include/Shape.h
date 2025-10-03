#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

class Shape {
public:
  virtual ~Shape() = default;

  virtual void print() const = 0;
  virtual double area() const = 0;
  virtual double volume() const = 0;
  virtual void draw() const = 0;
};

class TwoDShape : public Shape {
public:
  double volume() const override { return 0.0; }
};

class ThreeDShape : public Shape {};

#endif