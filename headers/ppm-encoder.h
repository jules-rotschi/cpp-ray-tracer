#ifndef PPM_ENCODER_H
#define PPM_ENCODER_H

#include <fstream>

#include "image.h"

class PpmEncoder {
public:
  void encode(const Image &image, std::ofstream &file) const;
};

#endif