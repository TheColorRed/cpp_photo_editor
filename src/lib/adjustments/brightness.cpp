#include "brightness.h"

void Brightness::apply(shared_ptr<Image> image, double value) {
  static int colors[3] = {0, 0, 0};
  auto lambda = [value, image](const int r, const int g, const int b, int index) {
    int red = r, green = g, blue = b;
    red += value;
    green += value;
    blue += value;
    colors[0] = red;
    colors[1] = green;
    colors[2] = blue;

    double threshold = 255.999;
    int m = max(red, max(green, blue));
    if (m <= threshold) {
      return colors;
    }

    double total = red + green + blue;
    if (total >= 3 * threshold) {
      colors[0] = colors[1] = colors[2] = int(threshold);
      return colors;
    }

    double x = (3 * threshold - total) / (3 * m - total);
    double gray = threshold - x * m;

    colors[0] = gray + x * red;
    colors[1] = gray + x * green;
    colors[2] = gray + x * blue;

    return colors;
  };
  image->mapRGB(lambda);
}