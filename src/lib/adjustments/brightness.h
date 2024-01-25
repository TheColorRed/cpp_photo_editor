#pragma once

#include <memory>

#include "adjust.h"

using namespace std;

class Brightness : public Adjust {
public:
  static void apply(shared_ptr<Image> image, double value);
};