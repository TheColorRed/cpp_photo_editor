#pragma once

#include <memory>

#include "adjust.h"

using namespace std;

class Contrast : public Adjust {
public:
  static void apply(shared_ptr<Image> image, int value);
};
