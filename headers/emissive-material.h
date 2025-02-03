#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "diffuse-material.h"

class Emissive : public Diffuse {
public:
  Emissive(const Color& albedo, const Color& emitted_color, double light_intensity);
};

#endif