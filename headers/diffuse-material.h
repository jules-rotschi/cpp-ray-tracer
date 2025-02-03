#ifndef DIFFUSE_MATERIAL_H
#define DIFFUSE_MATERIAL_H

#include "material.h"

class Diffuse : public Material {
public:
  Diffuse(const Color& albedo);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;
};

#endif