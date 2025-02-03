#ifndef METALIC_MATERIAL_H
#define METALIC_MATERIAL_H

#include "material.h"

class Metallic : public Material {
public:
  Metallic(Color albedo, double fuzziness);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;
};

#endif