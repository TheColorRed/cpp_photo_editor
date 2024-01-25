#include "raw.h"

using namespace std;

shared_ptr<Image> Raw::load() {
  // auto m_raw_proc = new LibRaw;
  // m_raw_proc->imgdata.params.use_camera_wb = 1;
  // m_raw_proc->imgdata.params.output_bps = 16;
  // m_raw_proc->imgdata.params.output_color = 1;
  // m_raw_proc->imgdata.params.gamm[0] = 1;
  // m_raw_proc->imgdata.params.gamm[1] = 1;
  // m_raw_proc->imgdata.params.highlight = 0;
  // m_raw_proc->imgdata.params.no_auto_bright = 0;
  // m_raw_proc->imgdata.params.user_qual = 0;
  // auto ret = m_raw_proc->open_buffer(data, size);
  auto image = Image::create(0, 0);
  return image;
}

bool Raw::save(string path, shared_ptr<Image> image) {
  return false;
}