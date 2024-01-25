#include "exposure.h"

using namespace std;

void Exposure::apply(shared_ptr<Image> image, double value) {
  static int colors[3] = {0, 0, 0};
  auto lambda = [value](int r, int g, int b) {
    colors[0] = r * value;
    colors[1] = g * value;
    colors[2] = b * value;

    return colors;
  };

  image->mapRGB(lambda);
}