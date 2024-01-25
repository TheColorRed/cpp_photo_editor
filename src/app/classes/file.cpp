#include "file.h"

File::File(string file_path) {
  this->path = file_path;
  this->name = file_path.substr(file_path.find_last_of("/\\") + 1);
  this->ext = file_path.substr(file_path.find_last_of(".") + 1);
}

File* File::create(string file_path) {
  auto file = new File(file_path);
  file->load();
  return file;
}

void File::load() {
  auto loader = Loader::get(this->path);
  this->image = loader->load();
}
