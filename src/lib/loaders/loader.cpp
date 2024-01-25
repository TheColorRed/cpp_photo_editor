
#include "jpeg/jpeg.h"
#include "loader.h"
#include "png/png.h"
#include "raw/raw.h"

using namespace std;

shared_ptr<Loader> Loader::get(string& path) {
  string ext(path);
  ext = ext.substr(ext.rfind(".") + 1);

  auto mime_type = mimeType(ext);

  shared_ptr<Loader> loader;
  if (mime_type == "image/jpeg") {
    loader = make_shared<Jpeg>(path);
  } else if (mime_type == "image/png") {
    loader = make_shared<Png>(path);
  } else if (mime_type == "image/x-adobe-dng") {
    loader = make_shared<Raw>(path);
  } else {
    throw "Error: File type not supported";
  }

  return loader;
}

void Loader::set(string path, shared_ptr<Image> image) {
  string ext(path);
  ext = ext.substr(ext.rfind(".") + 1);

  auto mime_type = mimeType(ext);

  shared_ptr<Loader> loader;
  if (mime_type == "image/jpeg") {
    loader = make_shared<Jpeg>(path);
  } else if (mime_type == "image/png") {
    loader = make_shared<Png>(path);
  } else if (mime_type == "image/x-adobe-dng") {
    loader = make_shared<Raw>(path);
  } else {
    throw "Error: File type not supported";
  }

  loader->save(path, image);
}

FILE* Loader::readFile() {
  FILE* fp = fopen(this->path.c_str(), "rb");

  if (fp == NULL) {
    throw "Error: File not found";
  }

  return fp;
}

string Loader::mimeType(const string& path) {
  string ext(path);
  ext = ext.substr(ext.rfind(".") + 1);

  string mime_type;
  if (ext == "jpeg" || ext == "jpg") {
    return "image/jpeg";
  } else if (ext == "png") {
    return "image/png";
  } else if (ext == "dng") {
    return "image/x-adobe-dng";
  } else {
    throw "Error: File type not supported";
  }
}