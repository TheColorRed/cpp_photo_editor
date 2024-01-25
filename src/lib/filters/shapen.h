#pragma once

#include "filter.h"

using namespace std;

class Sharpen : Filter {
public:
  static void apply(shared_ptr<Image> image, int amount);
};