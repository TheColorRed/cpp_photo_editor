#pragma once

#include "adjust.h"

class Threshold : public Adjust {
public:
  /**
   * Adjusts the image by applying a threshold filter where all colors below the threshold are set to 0 and all colors above the threshold are set to 255.
   * @param image The image to apply the adjustment to.
   * @param threshold The threshold to use.
  */
  static void apply(shared_ptr<Image> image, int threshold);
};