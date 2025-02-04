#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
class Hit;

#include "color.h"

class Material {
public:
  Color albedo;
  Color emitted_color;
  Material(const Color& albedo, const Color& emitted_color = Color(0, 0, 0));
  virtual bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const = 0;
};

class Diffuse : public Material {
public:
  Diffuse(const Color& albedo);
  Diffuse(const Color& albedo, const Color& emitted_color);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;
};

class Metallic : public Material {
public:
  Metallic(Color albedo, double roughness);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;

private:
  double roughness;
};

class Emissive : public Diffuse {
public:
  Emissive(const Color& albedo, const Color& emitted_color, double light_intensity);
};

#endif