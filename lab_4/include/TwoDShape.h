#ifndef TWODSHAPE_H
#define TWODSHAPE_H

#include <iostream>
#include "Shape.h"
#include "../include/constants.h"

class TwoDShape : public Shape {
public:
  double volume() const override { return 0.0; }
};

#endif