#include "emissive-material.h"

Emissive::Emissive(const Color& albedo, const Color& emitted_color, double light_intensity)
  : Diffuse(albedo, emitted_color * light_intensity) {}