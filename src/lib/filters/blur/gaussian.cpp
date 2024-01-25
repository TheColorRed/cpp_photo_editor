#include <cmath>

#include "box.h"
#include "gaussian.h"

// TODO: Optimize this filter.
// References:
//   - https://melatonin.dev/blog/implementing-marios-stack-blur-15-times-in-cpp/
//   - https://blog.ivank.net/fastest-gaussian-blur.html
//   - https://www.peterkovesi.com/papers/FastGaussianSmoothing.pdf
void Gaussian::apply(shared_ptr<Image> image, int radius) {
  auto clone = image->copy();
  static int rgb[3] = {0, 0, 0};
  auto lambda = [clone, image, radius](int r, int g, int b, int index) {
    // auto h = image->neighboringPixelAverage(index, radius, "horizontal");
    // auto v = image->neighboringPixelAverage(index, radius, "vertical");
    return image->surroundingPixelAverage(index, radius);
    // int v[3] = {0, 0, 0};
    // printf("%d %d %d\n", h[0], h[1], h[2]);
    // rgb[0] = (v[0] + h[0]) / 2;
    // rgb[1] = (v[1] + h[1]) / 2;
    // rgb[2] = (v[2] + h[2]) / 2;
    // return rgb;
  };
  clone->mapRGB(lambda);
  image->paste(clone);
}

// vector<int> Gaussian::boxesForGauss(double sigma, int n)  // standard deviation, number of boxes
// {
//   auto wIdeal = sqrt((12 * sigma * sigma / n) + 1);  // Ideal averaging filter width
//   int wl = floor(wIdeal);
//   if (wl % 2 == 0)
//     wl--;
//   auto wu = wl + 2;

//   auto mIdeal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
//   auto m = round(mIdeal);
//   // auto sigmaActual = Math.sqrt( (m*wl*wl + (n-m)*wu*wu - n)/12 );

//   vector<int> sizes;
//   for (auto i = 0; i < n; i++) sizes.push_back(i < m ? wl : wu);
//   return sizes;
// }