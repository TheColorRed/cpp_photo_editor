#include <cmath>

#include "../image.h"
#include "gamma.h"

using namespace std;

void Gamma::apply(shared_ptr<Image> image, double value) {
  static int colors[3] = {0, 0, 0};
  auto lambda = [value](int r, int g, int b) {
    colors[0] = pow(r / 255.0, 1 / value) * 255;
    colors[1] = pow(g / 255.0, 1 / value) * 255;
    colors[2] = pow(b / 255.0, 1 / value) * 255;

    return colors;
  };

  image->mapRGB(lambda);
}