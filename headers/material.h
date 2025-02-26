#ifndef MATERIAL_H
#define MATERIAL_H

class Ray;
class Hit;

#include "color.h"

class Material {
public:
  Color albedo;
  Color emitted_color;
  Material(const Color& albedo, double roughness, const Color& emitted_color = Color(0, 0, 0));
  virtual bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const = 0;

protected:
  double roughness = 0;
};

class Opaque : public Material {
public:
  Opaque(const Color& albedo, double roughness, double shine);
  Opaque(const Color& albedo, const Color& emitted_color);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;

private:
  double shine = 0;
};

class Emissive : public Opaque {
public:
  Emissive(const Color& albedo, const Color& emitted_color, double lightness);
};

class Clear : public Material {
public:
  double refractive_index;
  Clear(double refractive_index, const Color& albedo, double roughness);
  bool scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const override;
};

#endif