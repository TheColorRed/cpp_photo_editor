#include "threshold.h"

void Threshold::apply(shared_ptr<Image> image, int threshold) {
  static int colors[3] = {0, 0, 0};
  auto lambda = [threshold](int r, int g, int b) {
    int avg = (r + g + b) / 3;
    if (avg < threshold) {
      colors[0] = 0;
      colors[1] = 0;
      colors[2] = 0;
    } else {
      colors[0] = 255;
      colors[1] = 255;
      colors[2] = 255;
    }
    return colors;
  };
  image->mapRGB(lambda);
}