#pragma once

#include "color.h"

class HSLColor : public Color {
public:
  int h;
  int s;
  int l;

  HSLColor(int h, int s, int l) {
    this->h = h;
    this->s = s;
    this->l = l;
  }
};
