#include "image.h"

std::ostream& operator<<(std::ostream& output, PixelColor pixel) {
  output << pixel.red << " " << pixel.green << " " << pixel.blue;
  return output;
}

Image::Image(int width, int height)
  : width(width), height(height) {
  m_data = new PixelColor[width * height];
}

PixelColor Image::get_pixel(int row, int column) const {
  int safe_row = row > height - 1 ? height - 1 : row;
  int safe_column = column > width - 1 ? width - 1 : column;
  return m_data[safe_row * width + safe_column];
}

void Image::set_pixel(int row, int column, const PixelColor& value) {
  int safe_row = row > height - 1 ? height - 1 : row;
  int safe_column = column > width - 1 ? width - 1 : column;
  m_data[safe_row * width + safe_column] = value;
}

Image::~Image() {
  delete[] m_data;
}