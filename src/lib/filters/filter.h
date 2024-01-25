#pragma once

#include <memory>

#include "../image.h"

using namespace std;

class Image;

class Filter {
private:
  shared_ptr<Image> image;

public:
  void gaussian(double radius);
  void box(int radius);

  explicit Filter(shared_ptr<Image> image) {
    this->image = image;
  }

  virtual ~Filter() = default;
};