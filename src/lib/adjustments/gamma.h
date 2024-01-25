#pragma once

#include "adjust.h"

using namespace std;

class Gamma : public Adjust {
public:
  static void apply(shared_ptr<Image> image, double gamma = 1.2);
};