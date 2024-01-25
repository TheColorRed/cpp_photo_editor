#include "saturation.h"

using namespace std;

void Saturation::apply(shared_ptr<Image> image, double value) {
  static int colors[3] = {0, 0, 0};
  auto lambda = [value](int r, int g, int b) {
    auto hsv = Color::rgbToHsv(r, g, b);
    hsv[1] = hsv[1] * value;
    auto rgb = Color::hsvToRgb(hsv[0], hsv[1], hsv[2]);
    colors[0] = rgb[0];
    colors[1] = rgb[1];
    colors[2] = rgb[2];

    return colors;
  };

  image->mapRGB(lambda);
}