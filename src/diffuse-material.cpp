#include "diffuse-material.h"
#include "vector3.h"
#include "object.h"
#include "ray.h"

Diffuse::Diffuse(const Color& albedo) : Material(albedo, 0) {}

bool Diffuse::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 scattered_direction = hit.unit_normal + random_unit_vector();
  if (scattered_direction.is_nearly_null()) {
    scattered_direction = hit.unit_normal;
  }
  scattered_ray = Ray(hit.point, scattered_direction);
  return true;
}