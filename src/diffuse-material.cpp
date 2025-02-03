#include "diffuse-material.h"
#include "vector3.h"
#include "object.h"
#include "ray.h"
#include "hit.h"

Diffuse::Diffuse(const Color& albedo) : Material(albedo) {}

Diffuse::Diffuse(const Color& albedo, const Color& emitted_color)
  : Material(albedo, 0, emitted_color) {}

bool Diffuse::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 scattered_direction = hit.unit_normal + random_unit_vector();
  if (scattered_direction.is_nearly_null()) {
    scattered_direction = hit.unit_normal;
  }
  scattered_ray = Ray(hit.point, scattered_direction);
  return true;
}