#pragma once

#include <memory>

#include "../filter.h"

using namespace std;

class Gaussian : Filter {
private:
  static vector<int> boxesForGauss(double sigma, int n);

public:
  static void apply(shared_ptr<Image> image, int amount);
};