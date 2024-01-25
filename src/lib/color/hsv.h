#pragma once

#include "color.h"

class HSVColor : public Color {
public:
  int h;
  int s;
  int v;

  HSVColor(int h, int s, int v) {
    this->h = h;
    this->s = s;
    this->v = v;
  }
};
