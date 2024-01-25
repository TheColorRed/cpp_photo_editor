#pragma once

#include <memory>
#include <vector>

class HSLColor;
class HSVColor;
class RGBColor;

using namespace std;

class Color {
public:
  static double cubicInterpolate(double c1, double c2, double c3, double c4, double x);
  /**
   * Cubic interpolation between two numbers.
   * @param c1 The first number.
   * @param c2 The second number.
   * @param x The interpolation value between 0 and 1.
   */
  static double cubicInterpolate(double c1, double c2, double x);
  /**
   * Linear interpolation between two numbers.
   * @param original The original number. aka the number when x is 0.
   * @param modified The modified number. aka the number when x is 1.
  */
  static int linearInterpolate(const int& original, const int& modified, const int& x);

  static int pixelAverage(int r, int g, int b) {
    return (r + g + b) / 3;
  }

  static shared_ptr<RGBColor> rgb(int r, int g, int b, double a = 255.0);
  static shared_ptr<HSLColor> hsl(int h, int s, int l, double a = 255.0);
  static shared_ptr<HSVColor> hsv(int h, int s, int v, double a = 255.0);

  static shared_ptr<HSLColor> rgbToHsl(int r, int g, int b);
  static int* rgbToHsv(int r, int g, int b);
  static int* rgbToHsv(shared_ptr<RGBColor> color);

  static shared_ptr<RGBColor> hslToRgb(int h, int s, int l);
  static int* hsvToRgb(int h, int s, int v);

  static double hueToRgb(double p, double q, double t);

  // Color(int r = 0, int g = 0, int b = 0) {
  //   this->r = r;
  //   this->g = g;
  //   this->b = b;
  // }

  virtual ~Color() = default;
};