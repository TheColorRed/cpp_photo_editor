#pragma once

#include "image.h"

using namespace std;

/**
 * A mask is a grayscale image that can be used to hide or show parts of another image.
 * Black pixels hide what is underneath while white pixels show it.
 * Gray pixels partially hide or show the image underneath.
 *
 * A mask can also be used to apply adjustments and filters to only parts of an image. The more white a pixel is, the more the adjustment or filter will be applied to the underlying pixel. The more black a pixel is, the less the adjustment or filter will be applied to the underlying pixel.
 */
class Mask : public Image {
public:
  /**
   * Create a mask with the given width and height.
   * No color information is stored in the mask, it must be added manually.
   * @param width The width of the mask.
   * @param height The height of the mask.
   */
  static shared_ptr<Mask> create(int width, int height) {
    auto mask = Image::create(width, height);
    return static_pointer_cast<Mask>(mask);
  }
  /**
   * Create a mask filled with black pixels.
   * @param width The width of the mask.
   * @param height The height of the mask.
   */
  static shared_ptr<Mask> black(int width, int height) {
    auto mask = Image::black(width, height);
    return static_pointer_cast<Mask>(mask);
  }
  /**
   * Create a mask filled with white pixels.
   * @param width The width of the mask.
   * @param height The height of the mask.
   */
  static shared_ptr<Mask> white(int width, int height) {
    auto mask = Image::white(width, height);
    return static_pointer_cast<Mask>(mask);
  }
  /**
   * Create a mask filled with gray pixels.
   * @param width The width of the mask.
   * @param height The height of the mask.
   * @param gray The gray value of the pixels.
   */
  static shared_ptr<Mask> gray(int width, int height, int gray) {
    auto mask = Mask::create(width, height);
    for (int i = 0; i < width * height; i++) {
      mask->addColor(gray);
    }
    return static_pointer_cast<Mask>(mask);
  }
  /**
   * Set the color of a pixel in the mask. This sets all channels to the same value.
   * @param index The index of the pixel.
   * @param gray The gray value of the pixel.
  */
  void setColor(int index, int gray) {
    Image::setColor(index, gray, gray, gray);
  }
  /**
   * Adds a color to the end of the mask. This sets all channels to the same value.
   * @param gray The gray value of the pixel.
   */
  void addColor(int gray) {
    Image::addColor(gray, gray, gray);
  }
  /**
   * Get the color of a pixel in the mask. All channels will have the same value.
   * @param index The index of the pixel.
   */
  int getColorAt(int index) {
    return Image::red[index];
  }

  // static shared_ptr<Image> from();
};
