#include <png.h>

#include <memory>
#include <string>

#include "../../color/color.h"
#include "../../color/rgb.h"
#include "png.h"

using namespace std;

shared_ptr<Image> Png::load() {
  int width = 0, height = 0;
  FILE *fp = this->readFile();

  png_byte bit_depth;
  png_byte color_type;
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_init_io(png, fp);
  png_read_info(png, info);

  width = png_get_image_width(png, info);
  height = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth = png_get_bit_depth(png, info);

  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);
  if (png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);
  if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  shared_ptr<Image> image = Image::create(width, height);

  int num_channels = 4;
  // Set up row pointer
  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
  unsigned int i, j;
  for (i = 0; i < height; i++)
    row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png, info));
  png_read_image(png, row_pointers);

  // Put row pointers data into image
  unsigned char *img = (unsigned char *)malloc(num_channels * width * height);
  for (i = 0; i < height; i += num_channels) {
    // shared_ptr<RGBColor> color = Color::rgb(row_pointers[i][0], row_pointers[i][1], row_pointers[i][2], row_pointers[i][3]);
    int r = row_pointers[i][0];
    int g = row_pointers[i][1];
    int b = row_pointers[i][2];
    int a = row_pointers[i][3];
    image->addColor(r, g, b, a);
  }
  fclose(fp);
  for (i = 0; i < height; i++)
    free(row_pointers[i]);
  free(row_pointers);

  return image;
}

bool Png::save(string path, shared_ptr<Image> image) {
  FILE *fp = fopen(path.c_str(), "wb");
  if (!fp) {
    fprintf(stderr, "Could not open file %s for writing\n", path.c_str());
    return false;
  }

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fprintf(stderr, "Could not allocate write struct\n");
    return false;
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fprintf(stderr, "Could not allocate info struct\n");
    return false;
  }

  if (setjmp(png_jmpbuf(png))) {
    fprintf(stderr, "Error during png creation\n");
    return false;
  }

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(png, info, image->width, image->height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
  // Use png_set_filler().
  // png_set_filler(png, 0, PNG_FILLER_AFTER);

  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * image->height);
  unsigned int i, j;
  for (i = 0; i < image->height; i++)
    row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png, info));

  for (i = 0; i < image->height; i++) {
    png_bytep row = row_pointers[i];
    for (j = 0; j < image->width; j++) {
      auto color = image->getPixel(i * image->width + j);
      row[j * 4] = color[0];
      row[j * 4 + 1] = color[1];
      row[j * 4 + 2] = color[2];
      row[j * 4 + 3] = 255;
      // row[j * 4] = color->r;
      // row[j * 4 + 1] = color->g;
      // row[j * 4 + 2] = color->b;
      // row[j * 4 + 3] = color->a;
    }
  }

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for (i = 0; i < image->height; i++)
    free(row_pointers[i]);
  return true;
}