#include <algorithm>
#include <iterator>

#include "image.h"
#include "mask.h"

using namespace std;

shared_ptr<Image> Image::copy() {
  auto image = Image::create(this->_width, this->_height);
  auto size = this->width * this->height;

  image->red = vector<uint8_t>(this->red);
  image->green = vector<uint8_t>(this->green);
  image->blue = vector<uint8_t>(this->blue);
  image->alpha = vector<uint8_t>(this->alpha);
  return image;
}

shared_ptr<Image> Image::copy(int x, int y, int width, int height) {
  auto image = Image::black(width, height);
  for (int row = y; row < y + height; row++) {
    for (int col = x; col < x + width; col++) {
      if (row >= 0 && row < this->height && col >= 0 && col < this->width) {
        int index = row * this->width + col;
        int sourceIndex = (row - y) * width + (col - x);
        image->red[sourceIndex] = this->red[index];
        image->green[sourceIndex] = this->green[index];
        image->blue[sourceIndex] = this->blue[index];
      }
    }
  }
  return image;
}

void Image::paste(shared_ptr<Image> source, int x, int y) {
  int width = source->width;
  int height = source->height;
  int sourceIndex = 0;
  int index = 0;
  for (int row = y; row < y + height; row++) {
    for (int col = x; col < x + width; col++) {
      if (row >= 0 && row < this->height && col >= 0 && col < this->width) {
        sourceIndex = (row - y) * width + (col - x);
        index = row * this->width + col;
        this->red[index] = source->red[sourceIndex];
        this->green[index] = source->green[sourceIndex];
        this->blue[index] = source->blue[sourceIndex];
      }
    }
  }
}

void Image::addColor(int r, int g, int b, int a) {
  this->red.push_back(r);
  this->green.push_back(g);
  this->blue.push_back(b);
  this->alpha.push_back(a);
}

void Image::setColor(int idx, int r, int g, int b, int a) {
  r = clamp(r, 0, 255);
  g = clamp(g, 0, 255);
  b = clamp(b, 0, 255);
  a = clamp(a, 0, 255);

  this->red[idx] = r;
  this->green[idx] = g;
  this->blue[idx] = b;
  this->alpha[idx] = a;
}

int* Image::getPixel(int index) {
  static int color[3] = {0, 0, 0};
  color[0] = this->red[index];
  color[1] = this->green[index];
  color[2] = this->blue[index];
  return color;
}

int* Image::getPixel(int x, int y) {
  return this->getPixel(y * this->width + x);
}

int* Image::getPixelCoords(int index) {
  static int coords[2] = {0, 0};
  coords[0] = index % this->width;
  coords[1] = index / this->width;
  return coords;
}

vector<unsigned char> Image::getRGBRow(int row) {
  auto data = vector<unsigned char>(this->_width * 3);
  for (int i = 0; i < this->width; i++) {
    data[i * 3] = this->red[row * this->width + i];
    data[i * 3 + 1] = this->green[row * this->width + i];
    data[i * 3 + 2] = this->blue[row * this->width + i];
  }
  return data;
}

int* Image::surroundingPixelAverage(const int& index, const int& size) {
  static int rgb[3] = {0, 0, 0};
  auto surrounding = surroundingPixels(index, size);
  int red = 0;
  int green = 0;
  int blue = 0;
  // The number of pixels that were ignored because they were not within the image.
  // This amount is subtracted from the total number of pixels to get the average.
  int ignored = 0;
  for (int i = 0; i < size * size * 3; i += 3) {
    if (surrounding[i] > -1) {
      red += surrounding[i];
      green += surrounding[i + 1];
      blue += surrounding[i + 2];
    } else {
      ignored++;
    }
  }
  int total = size * size - ignored;
  rgb[0] = red / total;
  rgb[1] = green / total;
  rgb[2] = blue / total;
  return rgb;
}

int* Image::neighboringPixelAverage(const int& index, const int& radius, const string direction) {
  static int* rgb = new int[3];
  rgb = neighboringPixels(index, radius, direction);
  int red = 0;
  int green = 0;
  int blue = 0;
  int total = 0;
  for (int i = 0; i < radius * 3; i += 3) {
    if (rgb[i] > -1) {
      red += rgb[i];
      green += rgb[i + 1];
      blue += rgb[i + 2];
      total++;
    }
  }
  rgb[0] = red / total;
  rgb[1] = green / total;
  rgb[2] = blue / total;
  return rgb;
}

int* Image::surroundingPixels(const int& index, const int& radius) {
  /*
  example: 3x3
  [
    [[0,0,0], [0,0,0], [0,0,0]],
    [[0,0,0], [0,0,0], [0,0,0]],
    [[0,0,0], [0,0,0], [0,0,0]]
  ]
  */
  static int* pixels = new int[radius * radius * 3];
  int half = radius / 2;
  int width = this->width;
  int height = this->height;
  int row = index / width;
  int col = index % width;
  for (int i = 0; i < radius; i++) {
    int r = row + i - half;
    for (int j = 0; j < radius; j++) {
      int c = col + j - half;
      if (r < 0 || r >= height || c < 0 || c >= width) {
        pixels[i * radius * 3 + j * 3] = -1;
        pixels[i * radius * 3 + j * 3 + 1] = -1;
        pixels[i * radius * 3 + j * 3 + 2] = -1;
      } else {
        pixels[i * radius * 3 + j * 3] = this->red[r * width + c];
        pixels[i * radius * 3 + j * 3 + 1] = this->green[r * width + c];
        pixels[i * radius * 3 + j * 3 + 2] = this->blue[r * width + c];
      }
    }
  }
  return pixels;
}

int* Image::neighboringPixels(const int& index, const int& radius, const string direction) {
  int half = radius / 2;
  int width = this->width;
  int height = this->height;
  int row = index / width;
  int col = index % width;
  static int rgb[3] = {0, 0, 0};
  if (direction == "horizontal") {
    for (int i = 0; i < radius; i++) {
      int c = col + i - half;
      if (c < 0 || c >= width) {
        rgb[i * 3] = -1;
        rgb[i * 3 + 1] = -1;
        rgb[i * 3 + 2] = -1;
      } else {
        rgb[i * 3] = this->red[row * width + c];
        rgb[i * 3 + 1] = this->green[row * width + c];
        rgb[i * 3 + 2] = this->blue[row * width + c];
      }
    }
  } else if (direction == "vertical") {
    for (int i = 0; i < radius; i++) {
      int r = row + i - half;
      if (r < 0 || r >= height) {
        rgb[i * 3] = -1;
        rgb[i * 3 + 1] = -1;
        rgb[i * 3 + 2] = -1;
      } else {
        rgb[i * 3] = this->red[r * width + col];
        rgb[i * 3 + 1] = this->green[r * width + col];
        rgb[i * 3 + 2] = this->blue[r * width + col];
      }
    }
  }
  return rgb;
}

int Image::imageColorAverage() {
  int width = this->width;
  int height = this->height;
  int total = 0;
  for (int i = 0; i < width * height; i++) {
    total += Color::pixelAverage(this->red[i], this->green[i], this->blue[i]);
  }
  return total / (width * height);
}

int Image::channelAverage(string channel) {
  int width = this->width;
  int height = this->height;
  int total = 0;
  if (channel == "r") {
    for (int i = 0; i < width * height; i++) {
      total += this->red[i];
    }
  } else if (channel == "g") {
    for (int i = 0; i < width * height; i++) {
      total += this->green[i];
    }
  } else if (channel == "b") {
    for (int i = 0; i < width * height; i++) {
      total += this->blue[i];
    }
  }
  return total / (width * height);
}

void Image::mapRGB(function<int*(const int&, const int&, const int&, const int&)> callback) {
  int width = this->width;
  int height = this->height;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int red = this->red[row * width + col];
      int green = this->green[row * width + col];
      int blue = this->blue[row * width + col];
      auto strength = this->getMaskStrengthAt(row * width + col);

      auto newColor = callback(red, green, blue, row * width + col);

      int newRed = Color::linearInterpolate(red, clamp(newColor[0], 0, 255), strength);
      int newGreen = Color::linearInterpolate(green, clamp(newColor[1], 0, 255), strength);
      int newBlue = Color::linearInterpolate(blue, clamp(newColor[2], 0, 255), strength);

      this->red[row * width + col] = newRed;
      this->green[row * width + col] = newGreen;
      this->blue[row * width + col] = newBlue;
    }
  }
}

void Image::mapRGB(function<int*(const int&, const int&, const int&)> callback) {
  int width = this->width;
  int height = this->height;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int red = this->red[row * width + col];
      int green = this->green[row * width + col];
      int blue = this->blue[row * width + col];
      auto strength = this->getMaskStrengthAt(row * width + col);

      auto newColor = callback(red, green, blue);

      int newRed = Color::linearInterpolate(red, clamp(newColor[0], 0, 255), strength);
      int newGreen = Color::linearInterpolate(green, clamp(newColor[1], 0, 255), strength);
      int newBlue = Color::linearInterpolate(blue, clamp(newColor[2], 0, 255), strength);

      this->red[row * width + col] = newRed;
      this->green[row * width + col] = newGreen;
      this->blue[row * width + col] = newBlue;
    }
  }
}

void Image::mapHSLColor(function<shared_ptr<HSLColor>(shared_ptr<HSLColor>)> callback) {
  int width = this->width;
  int height = this->height;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      // auto color = this->getColor(row * width + col);
      // auto hsl = Color::rgbToHsl(color->r, color->g, color->b);
      // shared_ptr<HSLColor> newColor = callback(hsl);
      // this->setColor(row * width + col, newColor);
    }
  }
}

void Image::mapHSVColor(function<shared_ptr<HSVColor>(shared_ptr<HSVColor>)> callback) {
  int width = this->width;
  int height = this->height;
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      auto color = this->getPixel(row * width + col);
      // auto hsv = Color::rgbToHsv(color);
      // shared_ptr<HSVColor> newColor = callback(hsv);
      // this->setColor(row * width + col, newColor);
    }
  }
}

void Image::mapChannel(function<int(const int&)> callback) {
  this->mapChannel("rgb", callback);
}

void Image::mapChannel(function<int(const int&, const int&)> callback) {
  this->mapChannel("rgb", callback);
}

void Image::mapChannel(string channel, function<int(const int&, const int&)> callback) {
  int width = this->width;
  int height = this->height;
  std::transform(channel.begin(), channel.end(), channel.begin(), ::tolower);
  vector<char> channels(channel.begin(), channel.end());
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int color = 0;
      int index = row * width + col;
      int strength = this->getMaskStrengthAt(index);
      for (int i = 0; i < channels.size(); i++) {
        switch (channels[i]) {
        case 'r':
          color = this->red[index];
          this->red[index] = Color::linearInterpolate(color, clamp(callback(color, i), 0, 255), strength);
          break;
        case 'g':
          color = this->green[index];
          this->green[index] = Color::linearInterpolate(color, clamp(callback(color, i), 0, 255), strength);
          break;
        case 'b':
          color = this->blue[index];
          this->blue[index] = Color::linearInterpolate(color, clamp(callback(color, i), 0, 255), strength);
          break;
        }
      }
    }
  }
}

void Image::mapChannel(string channel, function<int(const int&)> callback) {
  int width = this->width;
  int height = this->height;
  std::transform(channel.begin(), channel.end(), channel.begin(), ::tolower);
  vector<char> channels(channel.begin(), channel.end());
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int color = 0;
      int index = row * width + col;
      int strength = this->getMaskStrengthAt(index);
      for (int i = 0; i < channels.size(); i++) {
        switch (channels[i]) {
        case 'r':
          color = this->red[index];
          this->red[index] = Color::linearInterpolate(color, clamp(callback(color), 0, 255), strength);
          break;
        case 'g':
          color = this->green[index];
          this->green[index] = Color::linearInterpolate(color, clamp(callback(color), 0, 255), strength);
          break;
        case 'b':
          color = this->blue[index];
          this->blue[index] = Color::linearInterpolate(color, clamp(callback(color), 0, 255), strength);
          break;
        }
      }
    }
  }
}

double Image::getMaskStrengthAt(int index) {
  if (this->mask == nullptr) {
    return 1.0;
  }
  return this->mask->red[index] / 255.0;
}

shared_ptr<vector<uint8_t>> Image::getBuffer() {
  int size = this->width * this->height * 4;
  shared_ptr<vector<uint8_t>> buffer(new vector<uint8_t>(size, 0));

  auto ref = buffer.get();
  for (int i = 0; i < this->width * this->height; i++) {
    ref->at(i * 4) = this->red[i];
    ref->at(i * 4 + 1) = this->green[i];
    ref->at(i * 4 + 2) = this->blue[i];
    ref->at(i * 4 + 3) = this->alpha[i];
  }

  return buffer;
}
