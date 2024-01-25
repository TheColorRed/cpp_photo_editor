// #include <cmath>

#include "auto.h"
#include "brightness.h"
#include "contrast.h"
#include "gamma.h"
#include "saturation.h"
#include "white-balance.h"

using namespace std;

void Auto::apply(shared_ptr<Image> image, double whitePoint) {
  image->adjust->whiteBalance(whitePoint);
  image->adjust->brightness(1.2);
  image->adjust->contrast(1.2);
  image->adjust->saturation(1.2);
  image->adjust->gamma(1.2);
  // WhiteBalance::apply(image, whitePoint);
  // Contrast::apply(image, 1.2);
  // Saturation::apply(image, 1.2);
  // // Brightness::apply(image, 1.2);
  // Gamma::apply(image, 1.2);

  // static int colors[3] = {0, 0, 0};
  // auto lambda = [](int r, int g, int b) {
  //   auto average = Color::pixelAverage(r, g, b);

  //   int red = r;
  //   int green = g;
  //   int blue = b;

  //   // Apply color balancing.
  //   if (average > 0) {
  //     colors[0] = r * 255 / average;
  //     colors[1] = g * 255 / average;
  //     colors[2] = b * 255 / average;
  //   }

  //   // Apply contrast.
  //   red = (red - 128) * 1.2 + 128;
  //   green = (green - 128) * 1.2 + 128;
  //   blue = (blue - 128) * 1.2 + 128;

  //   // Apply saturation.
  //   auto hsv = Color::rgbToHsv(red, green, blue);
  //   hsv[1] = hsv[1] * 1.2;
  //   auto rgb = Color::hsvToRgb(hsv[0], hsv[1], hsv[2]);
  //   red = rgb[0];
  //   green = rgb[1];
  //   blue = rgb[2];

  //   // Apply brightness.
  //   red = red * 1.2;
  //   green = green * 1.2;
  //   blue = blue * 1.2;

  //   // Apply gamma correction.
  //   red = pow(red / 255.0, 1 / 1.2) * 255;
  //   green = pow(green / 255.0, 1 / 1.2) * 255;
  //   blue = pow(blue / 255.0, 1 / 1.2) * 255;

  //   // Apply color balancing.
  //   if (average > 0) {
  //     red = red * average / 255;
  //     green = green * average / 255;
  //     blue = blue * average / 255;
  //   }

  //   colors[0] = red;
  //   colors[1] = green;
  //   colors[2] = blue;

  //   return colors;
  // };

  // image->mapRGBColor(lambda);
}