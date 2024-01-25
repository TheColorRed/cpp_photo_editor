#pragma once

#include <memory>

#include "../image.h"

using namespace std;

class Image;

class Adjust {
private:
  shared_ptr<Image> image;

public:
  void brightness(double value);
  void contrast(double value);
  void threshold(int value);
  void invert();
  void gamma(double value);
  void exposure(double value);
  void autoAdjust(double value);
  void saturation(double value);
  void whiteBalance(double value);

  explicit Adjust(shared_ptr<Image> image) {
    this->image = image;
  }

  virtual ~Adjust() = default;
};
