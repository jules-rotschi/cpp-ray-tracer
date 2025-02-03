#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
class Hit;

#include "color.h"

class Material {
public:
  Color albedo;
  Color emitted_color;
  Material(const Color& albedo, double fuzziness = 0, const Color& emitted_color = Color(0, 0, 0));
  virtual bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const = 0;

protected:
  double fuzziness;
};

#endif