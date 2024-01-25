#pragma once

#include "adjust.h"

class Saturation : public Adjust {
public:
  static void apply(shared_ptr<Image> image, double value);
};