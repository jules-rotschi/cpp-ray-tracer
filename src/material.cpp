#include "material.h"
#include "color.h"

Material::Material(const Color& albedo, double fuzziness, const Color& emitted_color)
  : albedo(albedo), fuzziness(fuzziness), emitted_color(emitted_color) {}