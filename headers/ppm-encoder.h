#ifndef PPM_ENCODER_H
#define PPM_ENCODER_H

#include <fstream>

class Image;

class PpmEncoder {
public:
  PpmEncoder() = default;
  void encode(const Image& image, std::ofstream& file) const;
};

#endif