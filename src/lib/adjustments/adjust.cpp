#include "adjust.h"
#include "auto.h"
#include "brightness.h"
#include "contrast.h"
#include "exposure.h"
#include "gamma.h"
#include "invert.h"
#include "saturation.h"
#include "threshold.h"
#include "white-balance.h"

void Adjust::autoAdjust(double value) {
  Auto::apply(this->image, value);
}

void Adjust::brightness(double value) {
  Brightness::apply(this->image, value);
}

void Adjust::contrast(double value) {
  Contrast::apply(this->image, value);
}

void Adjust::exposure(double value) {
  Exposure::apply(this->image, value);
}

void Adjust::gamma(double value) {
  Gamma::apply(this->image, value);
}

void Adjust::invert() {
  Invert::apply(this->image);
}

void Adjust::saturation(double value) {
  Saturation::apply(this->image, value);
}

void Adjust::threshold(int value) {
  Threshold::apply(this->image, value);
}

void Adjust::whiteBalance(double value) {
  WhiteBalance::apply(this->image, value);
}