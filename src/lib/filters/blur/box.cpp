#include <cmath>

#include "box.h"

// See: https://blog.ivank.net/fastest-gaussian-blur.html

void Box::apply(shared_ptr<Image> image, int radius) {
  auto clone = image->copy();
  static int rgb[3] = {0, 0, 0};
  auto lambda = [image, clone, radius](int r, int g, int b, int index) {
    // Box::boxBlur(image, clone, image->width, image->height, radius);
    // return 0;

    return rgb;
  };
  image->mapRGB(lambda);
}

// void gaussBlur(scl, tcl, w, h, r) {
//   auto bxs = boxesForGauss(r, 3);
//   boxBlur(scl, tcl, w, h, (bxs[0] - 1) / 2);
//   boxBlur(tcl, scl, w, h, (bxs[1] - 1) / 2);
//   boxBlur(scl, tcl, w, h, (bxs[2] - 1) / 2);
// }
void Box::boxBlur(shared_ptr<Image> image, shared_ptr<Image> dest, int w, int h, int r) {
  boxBlurH(dest, image, w, h, r);
  // boxBlurT(image, dest, w, h, r);
  image->paste(dest);
}
void Box::boxBlurH(shared_ptr<Image> image, shared_ptr<Image> dest, int w, int h, int r) {
  // auto iarr = 1 / (r + r + 1);
  // for (auto i = 0; i < h; i++) {
  //   auto ti = i * w, li = ti, ri = ti + r;
  //   auto fv = image->getPixelAt(ti), lv = image->getPixelAt(ti + w - 1), val = (r + 1) * fv;
  //   for (auto j = 0; j < r; j++) val += image->getPixelAt(ti + j);
  //   for (auto j = 0; j <= r; j++) {
  //     val += image->getPixelAt(ri++) - fv;
  //     dest->setPixelAt(ti++, round(val * iarr));
  //   }
  //   for (auto j = r + 1; j < w - r; j++) {
  //     val += image->getPixelAt(ri++) - image->getPixelAt(li++);
  //     dest->setPixelAt(ti++, round(val * iarr));
  //   }
  //   for (auto j = w - r; j < w; j++) {
  //     val += lv - image->getPixelAt(li++);
  //     dest->setPixelAt(ti++, round(val * iarr));
  //   }
  // }
}
// void Box::boxBlurT(shared_ptr<Image> iamge, shared_ptr<Image> dest, int w, int h, int r) {
//   auto iarr = 1 / (r + r + 1);
//   for (auto i = 0; i < w; i++) {
//     auto ti = i, li = ti, ri = ti + r * w;
//     auto fv = iamge[ti], lv = iamge[ti + w * (h - 1)], val = (r + 1) * fv;
//     for (auto j = 0; j < r; j++) val += iamge[ti + j * w];
//     for (auto j = 0; j <= r; j++) {
//       val += iamge[ri] - fv;
//       dest[ti] = round(val * iarr);
//       ri += w;
//       ti += w;
//     }
//     for (auto j = r + 1; j < h - r; j++) {
//       val += iamge[ri] - iamge[li];
//       dest[ti] = round(val * iarr);
//       li += w;
//       ri += w;
//       ti += w;
//     }
//     for (auto j = h - r; j < h; j++) {
//       val += lv - iamge[li];
//       dest[ti] = round(val * iarr);
//       li += w;
//       ti += w;
//     }
//   }
// }