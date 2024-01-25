#pragma once

#include <png.h>

#include <memory>
#include <string>

#include "../../image.h"
#include "../loader.h"

using namespace std;

class Png : public Loader {
public:
  shared_ptr<Image> load() override;
  bool save(string path, shared_ptr<Image> image) override;

  Png(string path) {
    this->path = path;
  }
};