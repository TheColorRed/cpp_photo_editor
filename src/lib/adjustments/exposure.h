#pragma once

#include "adjust.h"

using namespace std;

class Exposure : public Adjust {
public:
  static void apply(shared_ptr<Image> image, double value);
};