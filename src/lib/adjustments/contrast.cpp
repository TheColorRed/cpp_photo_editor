#include "../mask.h"
#include "contrast.h"

void Contrast::apply(shared_ptr<Image> image, int value) {
  // double factor = (259.0 * (value + 255.0)) / (255.0 * (259.0 - value));
  double factor = (1000.0 * (value + 255.0)) / (255.0 * (1000.0 - value));

  static int rgb[3] = {0, 0, 0};
  auto lambda = [factor, image](int r, int g, int b, int index) {
    auto rf = factor * (r - 128.0) + 128.0;
    auto gf = factor * (g - 128.0) + 128.0;
    auto bf = factor * (b - 128.0) + 128.0;

    return rgb[0] = rf,
           rgb[1] = gf,
           rgb[2] = bf,
           rgb;
  };
  image->mapRGB(lambda);
}