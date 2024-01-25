#include <string.h>

#include <chrono>

#include "../lib/draw.h"
#include "args.h"

using namespace std::chrono;
using namespace std;

int main(int argc, char *argv[]) {
  auto args = new CliArgs(argv);
  args->parse();

  printf("Loading image from %s\n", args->input.c_str());
  shared_ptr<Loader> loader = Loader::get(args->input);
  auto image = loader->load();

  auto start = high_resolution_clock::now();
  for (int i = 0; i < args->size(); i++) {
    auto item = args->at(i);
    auto key = std::get<0>(item);
    auto value = std::get<1>(item);

    if (value.size() > 0) {
      printf("Found argument %s with value %s\n", key.c_str(), value[0].c_str());
    }

    // Apply image adjustments.
    if (key == "auto")
      image->adjust->autoAdjust(stod(value[0]));
    else if (key == "brightness")
      image->adjust->brightness(stod(value[0]));
    else if (key == "contrast")
      image->adjust->contrast(stod(value[0]));
    else if (key == "exposure")
      image->adjust->exposure(stod(value[0]));
    else if (key == "gamma")
      image->adjust->gamma(stod(value[0]));
    else if (key == "invert")
      image->adjust->invert();
    else if (key == "saturation")
      image->adjust->saturation(stod(value[0]));
    else if (key == "threshold")
      image->adjust->threshold(stoi(value[0]));
    else if (key == "white-balance")
      image->adjust->whiteBalance(stod(value[0]));

    // Apply image filters.
    else if (key == "gaussian")
      image->filter->gaussian(stoi(value[0]));
    else if (key == "box")
      image->filter->box(stoi(value[0]));

    // Apply drawing functions.
    else if (key == "circle") {
      int x = 0, y = 0, radius = 0, r = 0, g = 0, b = 0, a = 255;
      // formats: x,y,radius,r,g,b,a
      //          x,y,radius,string
      //          x,y,radius
      vector<string> values;
      char *token = strtok((char *)value[0].c_str(), ",");
      while (token != NULL) {
        values.push_back(token);
        token = strtok(NULL, ",");
      }
      if (values.size() == 3) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        radius = stoi(values[2]);
      } else if (values.size() == 4) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        radius = stoi(values[2]);
        auto color = values[3];
        if (color == "red") {
          r = 255;
          g = 0;
          b = 0;
        } else if (color == "green") {
          r = 0;
          g = 255;
          b = 0;
        } else if (color == "blue") {
          r = 0;
          g = 0;
          b = 255;
        } else if (color == "white") {
          r = 255;
          g = 255;
          b = 255;
        } else if (color == "black") {
          r = 0;
          g = 0;
          b = 0;
        }
      } else if (values.size() == 7) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        radius = stoi(values[2]);
        r = stoi(values[3]);
        g = stoi(values[4]);
        b = stoi(values[5]);
        a = stoi(values[6]);
      }
      image->draw->circle(x, y, radius, RGBColor(r, g, b, a));
    } else if (key == "line") {
      int x1 = 0, y1 = 0, x2 = 0, y2 = 0, r = 0, g = 0, b = 0, a = 255;
      // formats: x1,y1,x2,y2,r,g,b,a
      //          x1,y1,x2,y2,r,g,b
      //          x1,y1,x2,y2,string
      //          x1,y1,x2,y2
      vector<string> values;
      char *token = strtok((char *)value[0].c_str(), ",");
      while (token != NULL) {
        values.push_back(token);
        token = strtok(NULL, ",");
      }
      if (values.size() == 4) {
        x1 = stoi(values[0]);
        y1 = stoi(values[1]);
        x2 = stoi(values[2]);
        y2 = stoi(values[3]);
      } else if (values.size() == 5) {
        x1 = stoi(values[0]);
        y1 = stoi(values[1]);
        x2 = stoi(values[2]);
        y2 = stoi(values[3]);
        auto color = values[4];
        if (color == "red") {
          r = 255;
          g = 0;
          b = 0;
        } else if (color == "green") {
          r = 0;
          g = 255;
          b = 0;
        } else if (color == "blue") {
          r = 0;
          g = 0;
          b = 255;
        } else if (color == "white") {
          r = 255;
          g = 255;
          b = 255;
        } else if (color == "black") {
          r = 0;
          g = 0;
          b = 0;
        }
      } else if (values.size() == 8) {
        x1 = stoi(values[0]);
        y1 = stoi(values[1]);
        x2 = stoi(values[2]);
        y2 = stoi(values[3]);
        r = stoi(values[4]);
        g = stoi(values[5]);
        b = stoi(values[6]);
        a = stoi(values[7]);
      }
      image->draw->line(x1, y1, x2, y2, RGBColor(r, g, b, a));
    } else if (key == "rectangle") {
      int x = 0, y = 0, width = 0, height = 0, r = 0, g = 0, b = 0, a = 255;
      // formats: x,y,width,height,r,g,b,a
      //          x,y,width,height,r,g,b
      //          x,y,width,height,string
      //          x,y,width,height
      vector<string> values;
      char *token = strtok((char *)value[0].c_str(), ",");
      while (token != NULL) {
        values.push_back(token);
        token = strtok(NULL, ",");
      }
      if (values.size() == 4) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        width = stoi(values[2]);
        height = stoi(values[3]);
      } else if (values.size() == 5) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        width = stoi(values[2]);
        height = stoi(values[3]);
        auto color = values[4];
        if (color == "red") {
          r = 255;
          g = 0;
          b = 0;
        } else if (color == "green") {
          r = 0;
          g = 255;
          b = 0;
        } else if (color == "blue") {
          r = 0;
          g = 0;
          b = 255;
        } else if (color == "white") {
          r = 255;
          g = 255;
          b = 255;
        } else if (color == "black") {
          r = 0;
          g = 0;
          b = 0;
        }
      } else if (values.size() == 8) {
        x = stoi(values[0]);
        y = stoi(values[1]);
        width = stoi(values[2]);
        height = stoi(values[3]);
        r = stoi(values[4]);
        g = stoi(values[5]);
        b = stoi(values[6]);
        a = stoi(values[7]);
      }
      image->draw->rectangle(x, y, width, height, RGBColor(r, g, b, a));
    }
    // Apply image transformations.
    else if (key == "scale") {
      if (value[0].find("x") != string::npos && value[0].find("y") != string::npos) {
        auto x = value[0].substr(1, value[0].find("y") - 1);
        auto y = value[0].substr(value[0].find("y") + 1);
        image->transform->scale(stod(x), stod(y));
      } else if (value[0].rfind("x", 0) == 0) {
        auto val = value[0].substr(1);
        image->transform->scaleWidth(stoi(val));
      } else if (value[0].rfind("y", 0) == 0) {
        auto val = value[0].substr(1);
        image->transform->scaleHeight(stoi(val));
      } else {
        image->transform->scale(stod(value[0]));
      }
    } else if (key == "flip-h")
      image->transform->flipH();
    else if (key == "flip-v")
      image->transform->flipV();
    else if (key == "rotate")
      image->transform->rotate(stod(value[0]));
    else if (key == "shift") {
      bool wrap = true;
      if (value[0].rfind("!") == 0) {
        wrap = false;
        value[0] = value[0].substr(1);
      }
      if (value[0].find("x") != string::npos && value[0].find("y") != string::npos) {
        auto x = value[0].substr(1, value[0].find("y") - 1);
        auto y = value[0].substr(value[0].find("y") + 1);
        image->transform->shift(stoi(x), stoi(y), wrap);
      } else if (value[0].rfind("x", 0) == 0) {
        auto val = value[0].substr(1);
        image->transform->shift(stoi(val), 0, wrap);
      } else if (value[0].rfind("y", 0) == 0) {
        auto val = value[0].substr(1);
        image->transform->shift(0, stoi(val), wrap);
      }

      else if (key == "mask") {
        // auto mask = Mask::create(image->width, image->height);
        // image->addMask(mask);
      }
    }

    else if (key == "red") {
      auto redImage = Image::black(image->width, image->height);
      redImage->red = vector<uint8_t>(image->red);
      redImage->green = vector<uint8_t>(image->red);
      redImage->blue = vector<uint8_t>(image->red);
      image = redImage;
    } else if (key == "blue") {
      auto blueImage = Image::black(image->width, image->height);
      blueImage->red = vector<uint8_t>(image->blue);
      blueImage->green = vector<uint8_t>(image->blue);
      blueImage->blue = vector<uint8_t>(image->blue);
      image = blueImage;
    } else if (key == "green") {
      auto greenImage = Image::black(image->width, image->height);
      greenImage->red = vector<uint8_t>(image->green);
      greenImage->green = vector<uint8_t>(image->green);
      greenImage->blue = vector<uint8_t>(image->green);
      image = greenImage;
    }
  }

  auto maskWhite = Mask::white(image->width, image->height);
  auto maskBlack = Mask::black(image->width, image->height);

  maskWhite->draw->circle(300, 150, 200, RGBColor(0, 0, 0));
  maskBlack->draw->circle(300, 150, 200, RGBColor(255, 255, 255));

  image->addMask(maskBlack);
  image->adjust->contrast(150);

  image->addMask(maskWhite);
  image->adjust->brightness(100);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  printf("Finished processing image in %dms\n", duration.count());

  if (args->output.size() == 0) {
    printf("No output file(s) specified\n");
    exit(1);
  }

  for (int i = 0; i < args->output.size(); i++) {
    string output = args->output[i];
    printf("Saving image to %s\n", output.c_str());
    Loader::set(output, image);
  }
}