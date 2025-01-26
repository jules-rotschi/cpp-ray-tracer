#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <array>

#include "constants.h"

struct PixelColor {
  int red;
  int green;
  int blue;
};

std::ostream &operator<<(std::ostream &output, PixelColor pixel);

class Image {
private:
  PixelColor *m_data;

public:
  int width;
  int height;
  double aspect_ratio;

  Image() = delete;
  Image(int width, int height);

  PixelColor get_pixel(int row, int column) const;
  void set_pixel(int row, int column, const PixelColor &value);

  ~Image();
};

#endif