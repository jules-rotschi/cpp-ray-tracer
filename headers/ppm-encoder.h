#ifndef PPM_ENCODER_H
#define PPM_ENCODER_H

#include <fstream>

#include "image.h"

class PpmEncoder {
public:
  void encode(std::shared_ptr<Image> const image, std::ofstream &file) const;
};

#endif