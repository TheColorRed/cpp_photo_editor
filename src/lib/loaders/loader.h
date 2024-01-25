#pragma once

#include <memory>
#include <string>

#include "../image.h"

using namespace std;

class Loader {
protected:
  string path;

public:
  virtual shared_ptr<Image> load() = 0;
  virtual bool save(string path, shared_ptr<Image> image) = 0;

  static shared_ptr<Loader> get(string& path);
  static void set(string path, shared_ptr<Image> image);
  static string mimeType(const string& path);

  FILE* readFile();
};