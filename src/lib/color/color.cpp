#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "color.h"
#include "hsl.h"
#include "hsv.h"
#include "rgb.h"

using namespace std;

shared_ptr<RGBColor> Color::rgb(int r, int g, int b, double a) {
  return make_shared<RGBColor>(r, g, b);
}

shared_ptr<HSLColor> Color::hsl(int h, int s, int l, double a) {
  return make_shared<HSLColor>(h, s, l);
}

shared_ptr<HSVColor> Color::hsv(int h, int s, int v, double a) {
  return make_shared<HSVColor>(h, s, v);
}

double Color::cubicInterpolate(double c1, double c2, double c3, double c4, double x) {
  return c2 + 0.5 * x * (c3 - c1 + x * (2.0 * c1 - 5.0 * c2 + 4.0 * c3 - c4 + x * (3.0 * (c2 - c3) + c4 - c1)));
}

double Color::cubicInterpolate(double c1, double c2, double x) {
  return Color::cubicInterpolate(c1, c2, c1, c2, x);
}

int Color::linearInterpolate(const int& c1, const int& c2, const int& x) {
  return c1 * (1 - x) + c2 * x;
}

shared_ptr<RGBColor> Color::hslToRgb(int h, int s, int l) {
  h = clamp(h, 0, 360);
  s = clamp(s, 0, 100);
  l = clamp(l, 0, 100);
  auto rgb = vector<unsigned char>(3);
  auto r = 0.0;
  auto g = 0.0;
  auto b = 0.0;
  auto h1 = h / 255.0;
  auto s1 = s / 255.0;
  auto l1 = l / 255.0;
  if (s1 == 0) {
    r = g = b = l1;
  } else {
    auto q = l1 < 0.5 ? l1 * (1 + s1) : l1 + s1 - l1 * s1;
    auto p = 2 * l1 - q;
    r = hueToRgb(p, q, h1 + 1 / 3.0);
    g = hueToRgb(p, q, h1);
    b = hueToRgb(p, q, h1 - 1 / 3.0);
  }
  rgb[0] = r * 255;
  rgb[1] = g * 255;
  rgb[2] = b * 255;
  return make_shared<RGBColor>(rgb[0], rgb[1], rgb[2]);
}

double Color::hueToRgb(double p, double q, double t) {
  if (t < 0) {
    t += 1;
  }
  if (t > 1) {
    t -= 1;
  }
  if (t < 1 / 6.0) {
    return p + (q - p) * 6 * t;
  }
  if (t < 1 / 2.0) {
    return q;
  }
  if (t < 2 / 3.0) {
    return p + (q - p) * (2 / 3.0 - t) * 6;
  }
  return p;
}

shared_ptr<HSLColor> Color::rgbToHsl(int r, int g, int b) {
  int hsl[3] = {0};
  auto r1 = r / 255.0;
  auto g1 = g / 255.0;
  auto b1 = b / 255.0;
  auto l = fmax(fmax(r1, g1), b1);
  auto s = l - fmin(fmin(r1, g1), b1);
  auto h = s ? l == r1
                   ? (g1 - b1) / s
               : l == g1
                   ? 2 + (b1 - r1) / s
                   : 4 + (r1 - g1) / s
             : 0;

  hsl[0] = 60 * h < 0 ? 60 * h + 360 : 60 * h;
  hsl[1] = 100 * (s ? (l <= 0.5 ? s / (2 * l - s) : s / (2 - (2 * l - s))) : 0);
  hsl[2] = (100 * (2 * l - s)) / 2;

  return make_shared<HSLColor>(hsl[0], hsl[1], hsl[2]);
}

int* Color::rgbToHsv(shared_ptr<RGBColor> color) {
  return rgbToHsv(0, 0, 0);
  // return rgbToHsv(color->r, color->g, color->b);
}

int* Color::rgbToHsv(int r, int g, int b) {
  static int hsv[3] = {0, 0, 0};
  auto r1 = r / 255.0;
  auto g1 = g / 255.0;
  auto b1 = b / 255.0;
  auto max = fmax(fmax(r1, g1), b1);
  auto min = fmin(fmin(r1, g1), b1);
  auto h = 0.0;
  auto s = 0.0;
  auto v = max;
  auto d = max - min;
  s = max == 0 ? 0 : d / max;
  if (max == min) {
    h = 0;
  } else {
    if (max == r1) {
      h = (g1 - b1) / d + (g1 < b1 ? 6 : 0);
    } else if (max == g1) {
      h = (b1 - r1) / d + 2;
    } else if (max == b1) {
      h = (r1 - g1) / d + 4;
    }
    h /= 6;
  }
  hsv[0] = h * 255;
  hsv[1] = s * 255;
  hsv[2] = v * 255;
  return hsv;
}

int* Color::hsvToRgb(int h, int s, int v) {
  static int rgb[3] = {0, 0, 0};
  auto h1 = h / 255.0;
  auto s1 = s / 255.0;
  auto v1 = v / 255.0;
  auto r = 0.0;
  auto g = 0.0;
  auto b = 0.0;
  auto i = floor(h1 * 6);
  auto f = h1 * 6 - i;
  auto p = v1 * (1 - s1);
  auto q = v1 * (1 - f * s1);
  auto t = v1 * (1 - (1 - f) * s1);
  switch ((int)i % 6) {
  case 0:
    r = v1;
    g = t;
    b = p;
    break;
  case 1:
    r = q;
    g = v1;
    b = p;
    break;
  case 2:
    r = p;
    g = v1;
    b = t;
    break;
  case 3:
    r = p;
    g = q;
    b = v1;
    break;
  case 4:
    r = t;
    g = p;
    b = v1;
    break;
  case 5:
    r = v1;
    g = p;
    b = q;
    break;
  }
  rgb[0] = r * 255;
  rgb[1] = g * 255;
  rgb[2] = b * 255;
  return rgb;
}