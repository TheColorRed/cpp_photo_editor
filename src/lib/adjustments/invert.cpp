#include "invert.h"

void Invert::apply(shared_ptr<Image> image) {
  auto lambda = [](int value) {
    return 255 - value;
  };
  image->mapChannel(lambda);
}