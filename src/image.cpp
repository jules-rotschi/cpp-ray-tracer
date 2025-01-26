#include "image.h"

std::ostream &operator<<(std::ostream &output, PixelColor pixel) {
  output << pixel.red << " " << pixel.green << " " << pixel.blue;
  return output;
}

Image::Image(int width, int height)
  : width(width), height(height) {
  m_data = new PixelColor[width * height];
}

PixelColor Image::get_pixel(int row, int column) const {
  return m_data[row * width + column];
}

void Image::set_pixel(int row, int column, const PixelColor &value) {
  m_data[row * width + column] = value;
}

Image::~Image() {
  delete[] m_data;
}