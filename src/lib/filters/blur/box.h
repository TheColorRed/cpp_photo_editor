#pragma once

#include <memory>

#include "../filter.h"

using namespace std;

class Box : Filter {
private:
  static void boxBlur(shared_ptr<Image> scl, shared_ptr<Image> tcl, int w, int h, int r);
  static void boxBlurH(shared_ptr<Image> scl, shared_ptr<Image> tcl, int w, int h, int r);
  static void boxBlurT(shared_ptr<Image> scl, shared_ptr<Image> tcl, int w, int h, int r);

public:
  static void apply(shared_ptr<Image> image, int radius);
};