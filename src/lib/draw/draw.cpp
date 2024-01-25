#include <cmath>

#include "../color/rgb.h"
#include "draw.h"

void Draw::circle(int x, int y, int radius, RGBColor color) {
  auto image = this->image;
  static int rgb[3] = {0, 0, 0};
  auto lambda = [image, radius, color, x, y](int r, int g, int b, int index) {
    auto x1 = index % image->width;
    auto y1 = index / image->width;
    auto distance = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
    if (distance <= radius) {
      return rgb[0] = color.r, rgb[1] = color.g, rgb[2] = color.b, rgb;
    }

    return rgb[0] = r, rgb[1] = g, rgb[2] = b, rgb;
  };

  image->mapRGB(lambda);
}

void Draw::line(int x1, int y1, int x2, int y2, RGBColor color) {
  auto image = this->image;
  static int rgb[3] = {0, 0, 0};
  auto lambda = [image, color, x1, y1, x2, y2](int r, int g, int b, int index) {
    auto x = index % image->width;
    auto y = index / image->width;
    auto slope = (y2 - y1) / (x2 - x1);
    auto yIntercept = y1 - slope * x1;
    auto y3 = slope * x + yIntercept;
    if (y == y3) {
      return rgb[0] = color.r, rgb[1] = color.g, rgb[2] = color.b, rgb;
    }

    return rgb[0] = r, rgb[1] = g, rgb[2] = b, rgb;
  };

  image->mapRGB(lambda);
}

void Draw::rectangle(int x, int y, int width, int height, RGBColor color) {
  auto image = this->image;
  static int rgb[3] = {0, 0, 0};
  auto lambda = [image, color, x, y, width, height](int r, int g, int b, int index) {
    auto x1 = index % image->width;
    auto y1 = index / image->width;
    if (x1 >= x && x1 <= x + width && y1 >= y && y1 <= y + height) {
      return rgb[0] = color.r, rgb[1] = color.g, rgb[2] = color.b, rgb;
    }

    return rgb[0] = r, rgb[1] = g, rgb[2] = b, rgb;
  };

  image->mapRGB(lambda);
}

void Draw::gradient(int x, int y, int width, int height, RGBColor color1, RGBColor color2) {
  auto image = this->image;
  static int rgb[3] = {0, 0, 0};
  auto lambda = [image, color1, color2, x, y, width, height](int r, int g, int b, int index) {
    auto x1 = index % image->width;
    auto y1 = index / image->width;
    auto x2 = x + width;
    auto y2 = y + height;
    auto x3 = x1 - x;
    auto y3 = y1 - y;
    auto x4 = x2 - x;
    auto y4 = y2 - y;
    auto x5 = x3 / x4;
    auto y5 = y3 / y4;
    auto r1 = color1.r;
    auto g1 = color1.g;
    auto b1 = color1.b;
    auto r2 = color2.r;
    auto g2 = color2.g;
    auto b2 = color2.b;
    auto r3 = r1 + (r2 - r1) * x5;
    auto g3 = g1 + (g2 - g1) * x5;
    auto b3 = b1 + (b2 - b1) * x5;
    if (x1 >= x && x1 <= x + width && y1 >= y && y1 <= y + height) {
      return rgb[0] = r3, rgb[1] = g3, rgb[2] = b3, rgb;
    }

    return rgb[0] = r, rgb[1] = g, rgb[2] = b, rgb;
  };

  image->mapRGB(lambda);
}