#pragma once

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "adjustments/adjust.h"
#include "color/color.h"
#include "filters/filter.h"
// #include "mask.h"
#include "draw/draw.h"
#include "transforms/transform.h"

// using namespace std;

class Adjust;
class Filter;
class Transform;
class Mask;
class Draw;

class Image : public enable_shared_from_this<Image> {
private:
  /** The width of the image. */
  int _width;
  /** The height of the image. */
  int _height;

protected:
public:
  /** The width of the image. */
  const int& width = this->_width;
  /** The height of the image. */
  const int& height = this->_height;
  /** The image's red channel values. */
  vector<uint8_t> red;
  /** The image's green channel values. */
  vector<uint8_t> green;
  /** The image's blue channel values. */
  vector<uint8_t> blue;
  /** The image's alpha channel values. */
  vector<uint8_t> alpha;
  /** All the masks that are attached to the image. */
  shared_ptr<Mask> mask;
  /** Access to the adjustments that can be applied to the image. */
  shared_ptr<Adjust> adjust;
  /** Access to the filters that can be applied to the image. */
  shared_ptr<Filter> filter;
  /** Access to the transforms that can be applied to the image. */
  shared_ptr<Transform> transform;
  /** Access to the drawing functions that can be applied to the image. */
  shared_ptr<Draw> draw;
  /**
   * Gets the image's buffer buffer data.
   * The buffer is a vector of unsigned 8-bit integers that represent the image's RGBA values.
   * The buffer is in the order of red, green, blue, and alpha.
   */
  shared_ptr<vector<uint8_t>> getBuffer();
  /**
   * Sets the width of the image.
   */
  void setWidth(int width) {
    this->_width = width;
  }
  /**
   * Sets the height of the image.
   */
  void setHeight(int height) {
    this->_height = height;
  }
  /**
   * Adds a mask to the image.
   * @param mask The mask to add.
   */
  void addMask(shared_ptr<Mask> mask) {
    this->mask = mask;
  }
  /**
   * Removes the mask from the image.
   */
  void removeMask() {
    this->mask = nullptr;
  }
  shared_ptr<Image> fromGray() {
    auto grayImage = Image::create(this->width, this->height);
    for (int i = 0; i < this->width * this->height; i++) {
      auto gray = (this->red[i] + this->green[i] + this->blue[i]) / 3;
      grayImage->setColor(i, gray, gray, gray);
      // grayImage->addColor(gray, gray, gray);
    }
    return grayImage;
  }
  /**
   * Copies the image and returns it as a new image.
   */
  shared_ptr<Image> copy();
  /**
   * Copies a section of the image out and returns it as a new image.
   * @param x The x coordinate to cut from.
   * @param y The y coordinate to cut from.
   * @param width The width of the image to cut.
   * @param height The height of the image to cut.
   */
  shared_ptr<Image> copy(int x, int y, int width, int height);
  /**
   * Pastes the image data from another image into the current image.
   * @param source The image to paste.
   * @param x The x coordinate to paste the image at.
   * @param y The y coordinate to paste the image at.
   */
  void paste(shared_ptr<Image> source, int x = 0, int y = 0);
  /**
   * Adds color pixel information to the end of the image.
   */
  void addColor(int r, int g, int b, int a = 255);
  /**
   * Adds color pixel information to the end of the image.
   * @param r The red channel value.
   * @param g The green channel value.
   * @param b The blue channel value.
   */
  void setColor(int index, int r, int g, int b, int a = 255);
  /**
   * Gets a color pixel from the image at a specific index.
   * @param index The index of the color pixel.
   */
  int* getPixel(int index);
  /**
   * Gets a color from the image at a specific x and y coordinate.
   * @param x The x coordinate of the pixel.
   * @param y The y coordinate of the pixel.
  */
  int* getPixel(int x, int y);
  /**
   * Gets the x and y coordinates of a pixel at a specific index.
   * @param index The index of the pixel.
   */
  int* getPixelCoords(int index);
  /**
   * Gets the red channel value for a pixel.
   * @param index The index of the pixel.
   */
  int getRedChannel(int index) {
    return this->red[index];
  }
  /**
   * Gets the green channel value for a pixel.
   * @param index The index of the pixel.
   */
  int getGreenChannel(int index) {
    return this->green[index];
  }
  /**
   * Gets the blue channel value for a pixel.
   * @param index The index of the pixel.
   */
  int getBlueChannel(int index) {
    return this->blue[index];
  }
  /**
   * Gets the alpha channel value for a pixel.
   * @param index The index of the pixel.
   */
  int getAlphaChannel(int index) {
    return this->alpha[index];
  }
  /**
   * Sets the red channel value for a pixel.
   * The value is clamped between `0` and `255`.
   * @param index The index of the pixel.
   * @param value The value to set.
   */
  void setRedChannel(int index, int value) {
    this->red[index] = clamp(value, 0, 255);
  }
  /**
   * Sets the green channel value for a pixel.
   * The value is clamped between `0` and `255`.
   * @param index The index of the pixel.
   * @param value The value to set.
   */
  void setGreenChannel(int index, int value) {
    this->green[index] = clamp(value, 0, 255);
  }
  /**
   * Sets the blue channel value for a pixel.
   * The value is clamped between `0` and `255`.
   * @param index The index of the pixel.
   * @param value The value to set.
   */
  void setBlueChannel(int index, int value) {
    this->blue[index] = clamp(value, 0, 255);
  }
  /**
   * Sets the alpha channel value for a pixel.
   * The value is clamped between `0` and `255`.
   * @param index The index of the pixel.
   * @param value The value to set.
   */
  void setAlphaChannel(int index, int value) {
    this->alpha[index] = clamp(value, 0, 255);
  }
  /**
   * Gets an array of RGB values for a row of the image.
   * @param row The row to get.
   */
  vector<unsigned char> getRGBRow(int row);
  /**
   * Gets a vector of RGB values for a pixel and its surrounding pixels. If the pixel is on the edge of the image, the outside pixels will be -1.
   * @param index The index of the pixel.
   * @param size The size of the surrounding pixels to get. This should be an odd number of 3 or greater.
  */
  int* surroundingPixels(const int& index, const int& size);
  /**
   * Gets neighboring pixels in a specific direction.
   * @param index The index of the pixel.
   * @param size The size of the surrounding pixels to get. This should be an odd number of 3 or greater.
   * @param direction The direction to get the pixels. This can be 'horizontal' or 'vertical'.
   */
  int* neighboringPixels(const int& index, const int& size, const string direction);
  /**
   * Get the average color of the surrounding pixels.
   * @param index The index of the pixel.
   * @param size The size of the surrounding pixels to get. This should be an odd number of 3 or greater.
   */
  int* surroundingPixelAverage(const int& index, const int& size);
  /**
   * Get the average color of the neighboring pixels in a specific direction.
   * @param index The index of the pixel.
   * @param size The size of the surrounding pixels to get. This should be an odd number of 3 or greater.
   * @param direction The direction to get the pixels. This can be 'horizontal' or 'vertical'.
  */
  int* neighboringPixelAverage(const int& index, const int& size, const string direction);
  /**
   * Gets the average color of the image.
   */
  int imageColorAverage();
  /**
   * Gets the average color of a all channels in a pixel.
   * @param row The row to get.
   */
  int channelAverage(string channel);
  /**
   * Gets an array of HSL values for a row of the image.
   * @param row The row to get.
   */
  vector<unsigned char> getHSLRow(int row);
  /**
   * Maps each pixel in the image to a new color using the rgb color space.
   * The callback will pass in an int for each channel.
   * The callback expects an array of 3 ints to be returned (or the modified color).
   * @param callback The callback function to call for each pixel.
   */
  void mapRGB(function<int*(const int&, const int&, const int&)> callback);
  /**
   * Maps each pixel in the image to a new color using the rgb color space.
   * The callback will pass in an int for each channel and an int for the index of the pixel.
   * The callback expects an array of 3 ints to be returned (or the modified color).
   * @param callback The callback function to call for each pixel.
   */
  void mapRGB(function<int*(const int&, const int&, const int&, const int&)> callback);
  /**
   * Apply adjustments to specific RGB channels.
   * All returned values are clamped between `0` and `255`.
   * @param channel The channel to apply the adjustment to. This can be any combination of 'r', 'g', and 'b'.
   * @param callback The callback function that will be called for each pixel for each channel specified.
   */
  void mapChannel(string channel, function<int(const int&)> callback);
  void mapChannel(string channel, function<int(const int&, const int&)> callback);
  void mapChannel(function<int(const int&, const int&)> callback);
  /**
   * Apply adjustments to all RGB channels.
   * All returned values are clamped between `0` and `255`.
   * @param callback The callback function that will be called for each pixel for all `rgb` channels.
   */
  void mapChannel(function<int(const int&)> callback);
  /**
   * Maps each pixel in the image to a new color using the hsl color space.
   * The callback will pass in the current color and expects a new color to be returned (or the modified color).
   * @param callback The callback function to call for each pixel.
   */
  void mapHSLColor(function<shared_ptr<HSLColor>(shared_ptr<HSLColor>)> callback);
  /**
   * Maps each pixel in the image to a new color using the hsv color space.
   * The callback will pass in the current color and expects a new color to be returned (or the modified color).
   * @param callback The callback function to call for each pixel.
   */
  void mapHSVColor(function<shared_ptr<HSVColor>(shared_ptr<HSVColor>)> callback);

  static shared_ptr<Image> create(int width, int height) {
    // Prepare the image.
    shared_ptr<Image> image(new Image(width, height));
    auto size = width * height;

    // Set up the image's child classes.
    image->adjust = make_shared<Adjust>(image);
    image->filter = make_shared<Filter>(image);
    image->transform = make_shared<Transform>(image);
    image->draw = make_shared<Draw>(image);

    return image;
  }
  /**
   * Get the strength of the mask at a specific index.
   * If there is no mask, the strength will be 1.0.
   * * 0 means 100% so hide the pixel or apply no adjustment or filter.
   * * 0.5 means 50% so partially hide the pixel or apply a partial adjustment or filter.
   * * 1 means 100% so show the pixel or apply the full adjustment or filter.
   * @param index The index of the mask.
   */
  double getMaskStrengthAt(int index);

  static shared_ptr<Image> black(int width, int height) {
    auto image = Image::create(width, height);
    for (int i = 0; i < width * height; i++) {
      image->addColor(0, 0, 0);
    }
    return image;
  }

  static shared_ptr<Image> white(int width, int height) {
    auto image = Image::create(width, height);
    for (int i = 0; i < width * height; i++) {
      image->addColor(255, 255, 255);
    }
    return image;
  }

  /**
   * Creates a new image.
   * @param path The path of the image.
   * @param width The width of the image.
   * @param height The height of the image.
   */
  Image(int width, int height) {
    this->setWidth(width);
    this->setHeight(height);
  }

  virtual ~Image() = default;
};
