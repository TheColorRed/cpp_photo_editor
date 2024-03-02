#pragma once

#include <string>

#include "lib/draw.h"

using namespace std;

class File {
private:
  /**
   * The path to the file.
   */
  string path;
  /**
   * The name of the file without the extension.
   */
  string name;
  /**
   * The extension of the file including the dot.
   */
  string ext;
  /**
   * The image that is loaded from the file.
   */
  shared_ptr<Image> image;
  /**
   * Whether the file has been modified since the last save.
   */
  bool dirty = false;

  void load();
  File(string file_path);

public:
  static shared_ptr<File> create(string file_path);

  string getPath() {
    return path;
  }
  string getName() {
    return name;
  }
  string getExt() {
    return ext;
  }
  bool isDirty() {
    return dirty;
  }

  // shared_ptr<GdkTexture> getTexture();
};
