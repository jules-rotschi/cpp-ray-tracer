#include "metallic-material.h"
#include "ray.h"
#include "object.h"

Metallic::Metallic(Color albedo, double fuzziness) : Material(albedo, fuzziness) {}

bool Metallic::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 reflected_direction = incident_ray.get_direction().make_unit().reflect(hit.unit_normal);
  Vector3 fuzzy_direction = reflected_direction.make_unit() + fuzziness * random_unit_vector();
  scattered_ray = Ray(hit.point, fuzzy_direction);
  return true;
}