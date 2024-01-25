#include <math.h>

#include "transform.h"

void Transform::scale(double scale) {
  int width = this->image->width * scale;
  int height = this->image->height * scale;
  auto image = Image::black(width, height);
  int sourceIndex = 0;
  int index = 0;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      sourceIndex = (int)(row / scale) * this->image->width + (int)(col / scale);
      index = row * width + col;
      image->red[index] = this->image->red[sourceIndex];
      image->green[index] = this->image->green[sourceIndex];
      image->blue[index] = this->image->blue[sourceIndex];
    }
  }
  this->image->setWidth(width);
  this->image->setHeight(height);
  this->image->red = vector<uint8_t>(image->red);
  this->image->green = vector<uint8_t>(image->green);
  this->image->blue = vector<uint8_t>(image->blue);
}

void Transform::scale(int width, int height) {
  auto newImage = Image::black(width, height);
  int sourceIndex = 0;
  int index = 0;
  for (int row = 0; row < height; row++) {
    sourceIndex = (int)((double)row / height * this->image->height) * this->image->width;
    for (int col = 0; col < width; col++) {
      index = row * width + col;
      newImage->red[index] = this->image->red[sourceIndex];
      newImage->green[index] = this->image->green[sourceIndex];
      newImage->blue[index] = this->image->blue[sourceIndex];
      sourceIndex += (int)(this->image->width / width);
    }
  }
  this->image->setWidth(width);
  this->image->setHeight(height);
  this->image->red = vector<uint8_t>(newImage->red);
  this->image->green = vector<uint8_t>(newImage->green);
  this->image->blue = vector<uint8_t>(newImage->blue);
}

void Transform::scaleWidth(int width) {
  double scale = (double)width / this->image->width;
  this->scale(scale);
}

void Transform::scaleHeight(int height) {
  double scale = (double)height / this->image->height;
  this->scale(scale);
}

void Transform::flipH() {
  auto newImage = Image::black(this->image->width, this->image->height);
  int sourceIndex = 0;
  int index = 0;
  for (int row = 0; row < this->image->height; row++) {
    sourceIndex = row * this->image->width + this->image->width - 1;
    for (int col = 0; col < this->image->width; col++) {
      index = row * this->image->width + col;
      newImage->red[index] = this->image->red[sourceIndex];
      newImage->green[index] = this->image->green[sourceIndex];
      newImage->blue[index] = this->image->blue[sourceIndex];
      sourceIndex--;
    }
  }
  this->image->red = vector<uint8_t>(newImage->red);
  this->image->green = vector<uint8_t>(newImage->green);
  this->image->blue = vector<uint8_t>(newImage->blue);
}

void Transform::flipV() {
  auto newImage = Image::black(this->image->width, this->image->height);
  int sourceIndex = 0;
  int index = 0;
  for (int row = 0; row < this->image->height; row++) {
    sourceIndex = (this->image->height - row - 1) * this->image->width;
    for (int col = 0; col < this->image->width; col++) {
      index = row * this->image->width + col;
      newImage->red[index] = this->image->red[sourceIndex];
      newImage->green[index] = this->image->green[sourceIndex];
      newImage->blue[index] = this->image->blue[sourceIndex];
      sourceIndex++;
    }
  }
  this->image->red = vector<uint8_t>(newImage->red);
  this->image->green = vector<uint8_t>(newImage->green);
  this->image->blue = vector<uint8_t>(newImage->blue);
}

void Transform::rotate(double degrees) {
  double radians = degrees * M_PI / 180;
  int width = this->image->width;
  int height = this->image->height;
  int newWidth = (int)(abs(width * cos(radians)) + abs(height * sin(radians)));
  int newHeight = (int)(abs(width * sin(radians)) + abs(height * cos(radians)));
  auto newImage = Image::black(newWidth, newHeight);
  int sourceIndex = 0;
  int index = 0;
  int x = 0;
  int y = 0;
  for (int row = 0; row < newHeight; row++) {
    for (int col = 0; col < newWidth; col++) {
      x = (int)((col - newWidth / 2) * cos(radians) + (row - newHeight / 2) * sin(radians) + width / 2);
      y = (int)(-(col - newWidth / 2) * sin(radians) + (row - newHeight / 2) * cos(radians) + height / 2);
      if (x >= 0 && x < width && y >= 0 && y < height) {
        sourceIndex = y * width + x;
        index = row * newWidth + col;
        newImage->red[index] = this->image->red[sourceIndex];
        newImage->green[index] = this->image->green[sourceIndex];
        newImage->blue[index] = this->image->blue[sourceIndex];
      }
    }
  }
  this->image->setWidth(newWidth);
  this->image->setHeight(newHeight);
  this->image->red = vector<uint8_t>(newImage->red);
  this->image->green = vector<uint8_t>(newImage->green);
  this->image->blue = vector<uint8_t>(newImage->blue);
}

/**
 * TODO: fix this function
*/
void Transform::shift(int x, int y, bool wrap) {
  auto newImage = Image::black(this->image->width, this->image->height);
  // shift the image by the specified amount
  // if the wrap flag is true, wrap the image around the edges.
  // if the wrap flag is not false, use the color from `newImage`.
  int sourceIndex = 0;
  int index = 0;
  for (int row = 0; row < this->image->height; row++) {
    for (int col = 0; col < this->image->width; col++) {
      index = row * this->image->width + col;
      if (wrap) {
        newImage->red[index] = this->image->red[(row + y) % this->image->height * this->image->width + (col + x) % this->image->width];
        newImage->green[index] = this->image->green[(row + y) % this->image->height * this->image->width + (col + x) % this->image->width];
        newImage->blue[index] = this->image->blue[(row + y) % this->image->height * this->image->width + (col + x) % this->image->width];
      } else {
        if (row + y >= 0 && row + y < this->image->height && col + x >= 0 && col + x < this->image->width) {
          sourceIndex = (row + y) * this->image->width + (col + x);
          if (sourceIndex < 0) {
            sourceIndex = 0;
          }
          newImage->red[index] = this->image->red[sourceIndex];
          newImage->green[index] = this->image->green[sourceIndex];
          newImage->blue[index] = this->image->blue[sourceIndex];
        }
      }
    }
  }
  this->image->red = vector<uint8_t>(newImage->red);
  this->image->green = vector<uint8_t>(newImage->green);
  this->image->blue = vector<uint8_t>(newImage->blue);
}
