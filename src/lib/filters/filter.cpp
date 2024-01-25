#include "blur/box.h"
#include "blur/gaussian.h"
#include "filter.h"

using namespace std;

void Filter::gaussian(double radius) {
  Gaussian::apply(this->image, radius);
}

void Filter::box(int radius) {
  Box::apply(this->image, radius);
}