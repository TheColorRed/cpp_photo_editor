#include "jpeg.h"

#include <jpeglib.h>

#include <memory>
#include <string>

#include "../../color/color.h"
#include "../../color/rgb.h"

using namespace std;

shared_ptr<Image> Jpeg::load() {
  struct jpeg_decompress_struct info;
  struct jpeg_error_mgr err;

  int height, width, pixel_size, colorspace, i, j, k, res;
  info.err = jpeg_std_error(&err);
  info.out_color_components = 3;
  info.out_color_space = JCS_RGB;

  FILE* fp = this->readFile();

  jpeg_create_decompress(&info);
  jpeg_stdio_src(&info, fp);
  jpeg_read_header(&info, TRUE);
  jpeg_start_decompress(&info);

  width = info.output_width;
  height = info.output_height;
  const int size = width * height;

  shared_ptr<Image> image = Image::create(width, height);

  while (info.output_scanline < info.output_height) {
    unsigned char* buffer[1];
    buffer[0] = (unsigned char*)malloc(info.output_width * info.num_components);
    jpeg_read_scanlines(&info, buffer, 1);
    for (int i = 0; i < info.image_width * info.num_components; i += 3) {
      // shared_ptr<RGBColor> color = Color::rgb(buffer[0][i], buffer[0][i + 1], buffer[0][i + 2], 255);
      image->addColor(buffer[0][i], buffer[0][i + 1], buffer[0][i + 2]);
    }
    free(buffer[0]);
  }
  fclose(fp);
  return image;
}

bool Jpeg::save(string path, shared_ptr<Image> image) {
  struct jpeg_compress_struct info;
  struct jpeg_error_mgr jerr;

  FILE* outfile;
  JSAMPROW row_pointer[1];

  info.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&info);

  if ((outfile = fopen(path.c_str(), "wb")) == NULL) {
    // fprintf(stderr, "can't open %s\n", path);
    return false;
  }
  jpeg_stdio_dest(&info, outfile);

  info.image_width = image->width;
  info.image_height = image->height;
  info.input_components = 3;
  info.in_color_space = JCS_RGB;

  jpeg_set_defaults(&info);
  jpeg_set_quality(&info, 100, TRUE);
  jpeg_start_compress(&info, TRUE);

  for (int row = 0; row < image->height; row++) {
    auto rgbRow = image->getRGBRow(row);
    unsigned char* rowPointer = &rgbRow[0];
    row_pointer[0] = rowPointer;
    jpeg_write_scanlines(&info, row_pointer, 1);
  }

  jpeg_finish_compress(&info);
  fclose(outfile);
  jpeg_destroy_compress(&info);
  return true;
}
