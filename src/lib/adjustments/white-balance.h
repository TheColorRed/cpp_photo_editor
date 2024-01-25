#pragma once

#include "adjust.h"

class WhiteBalance : public Adjust {
public:
  static void apply(shared_ptr<Image> image, double value);
};