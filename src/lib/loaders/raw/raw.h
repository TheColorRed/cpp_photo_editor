#pragma once

// #include <libraw/libraw.h>

#include "../loader.h"

using namespace std;

class Loader;

class Raw : public Loader {
public:
  shared_ptr<Image> load() override;
  bool save(string path, shared_ptr<Image> image) override;

  Raw(string path) {
    this->path = path;
  }
};