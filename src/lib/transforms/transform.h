#pragma once

#include <memory>

#include "../image.h"

using namespace std;

class Image;

class Transform {
private:
  shared_ptr<Image> image;

public:
  explicit Transform(shared_ptr<Image> image) {
    this->image = image;
  }
  virtual ~Transform() = default;
  /**
   * Scales the image by a factor.
   * @param scale The factor to scale the image by.
   * Values less than 1 will shrink the image, values greater than 1 will enlarge the image.
   */
  void scale(double scale);
  /**
   * Scales the image to a specific width and height.
   * **Note:** The image will be stretched to fit the new dimensions.
   * @param width The width to scale the image to.
   * @param height The height to scale the image to.
   */
  void scale(int width, int height);
  /**
   * Scales the image to a specific width.
   * The height will then be scaled to maintain the aspect ratio.
   * @param width The width to scale the image to.
   */
  void scaleWidth(int width);
  /**
   * Scales the image to a specific height.
   * The width will then be scaled to maintain the aspect ratio.
   * @param height The height to scale the image to.
   */
  void scaleHeight(int height);
  /**
   * Flips the image along the horizontal axis.
   */
  void flipH();
  /**
   * Flips the image along the vertical axis.
   */
  void flipV();
  /**
   * Rotates the image by a number of degrees.
   * @param degrees The number of degrees to rotate the image by.
   */
  void rotate(double degrees);
  /**
   * Shifts the image by a certain number of pixels.
   * @param x The number of pixels to shift the image along the x-axis.
   * @param y The number of pixels to shift the image along the y-axis.
   * @param wrap Whether or not to wrap the image around the edges.
   */
  void shift(int x, int y, bool wrap = false);
};