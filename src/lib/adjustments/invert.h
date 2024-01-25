#pragma once

#include "adjust.h"

class Invert : public Adjust {
public:
  static void apply(shared_ptr<Image> image);
};