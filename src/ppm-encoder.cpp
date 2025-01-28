#include <fstream>
#include <iostream>
#include <memory>

#include "ppm-encoder.h"
#include "image.h"

void PpmEncoder::encode(const Image& image, std::ofstream& file) const {
  std::cout << "\nEncoding image..." << std::endl;

  file << "P3\n" << image.width << " " << image.height << "\n255\n";

  for (int row = 0; row < image.height; row++) {
    for (int column = 0; column < image.width; column++) {
      PixelColor pixel = image.get_pixel(row, column);
      file << pixel << '\n';
    }

    std::cout << "\rRemaining lines: " << image.height - row - 1 << std::flush;
  }

  std::cout << "\nImage has been encoded." << std::endl;
}