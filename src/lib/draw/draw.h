#pragma once

#include <memory>

#include "../image.h"

using namespace std;

class Draw {
private:
  shared_ptr<Image> image;

public:
  void circle(int x, int y, int radius, RGBColor color);
  void line(int x1, int y1, int x2, int y2, RGBColor color);
  void rectangle(int x, int y, int width, int height, RGBColor color);
  void gradient(int x, int y, int width, int height, RGBColor color1, RGBColor color2);

  Draw(shared_ptr<Image> image) {
    this->image = image;
  }
};