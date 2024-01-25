#include "white-balance.h"

using namespace std;

void WhiteBalance::apply(shared_ptr<Image> image, double value) {
  static int colors[3] = {0, 0, 0};
  auto average = image->imageColorAverage();
  auto lambda = [average, value](int r, int g, int b) {
    auto pixelAverage = Color::pixelAverage(r, g, b);

    // White balance.
    if (average > 0) {
      colors[0] = r * 255 / average / value;
      colors[1] = g * 255 / average / value;
      colors[2] = b * 255 / average / value;
    } else {
      colors[0] = r;
      colors[1] = g;
      colors[2] = b;
    }

    return colors;
  };

  image->mapRGB(lambda);
}