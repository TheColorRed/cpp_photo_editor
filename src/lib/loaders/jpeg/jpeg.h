#pragma once

#include <jpeglib.h>

#include "../loader.h"

class Loader;

using namespace std;

class Jpeg : public Loader {
public:
  shared_ptr<Image> load() override;
  bool save(string path, shared_ptr<Image> image) override;

  Jpeg(string path) {
    this->path = path;
  }
};