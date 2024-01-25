#pragma once

#include "color.h"

class RGBColor : public Color {
public:
  int r;
  int g;
  int b;
  int a;
  RGBColor(int r, int g, int b, int a = 255) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
};
