#include "material.h"
#include "color.h"
#include "vector3.h"
#include "ray.h"
#include "hit.h"

Material::Material(const Color& albedo, const Color& emitted_color)
  : albedo(albedo), emitted_color(emitted_color) {}

Diffuse::Diffuse(const Color& albedo) : Material(albedo) {}

Diffuse::Diffuse(const Color& albedo, const Color& emitted_color)
  : Material(albedo, emitted_color) {}

bool Diffuse::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 scattered_direction = hit.unit_normal + random_unit_vector_in_sphere();
  if (scattered_direction.is_nearly_null()) {
    scattered_direction = hit.unit_normal;
  }
  scattered_ray = Ray(hit.point, scattered_direction);
  return true;
}

Metallic::Metallic(Color albedo, double roughness) : Material(albedo), roughness(roughness) {}

bool Metallic::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 reflected_direction = incident_ray.get_direction().make_unit().reflect(hit.unit_normal);
  Vector3 fuzzy_direction = reflected_direction.make_unit() + roughness * random_unit_vector_in_sphere();
  scattered_ray = Ray(hit.point, fuzzy_direction);
  return true;
}

Emissive::Emissive(const Color& albedo, const Color& emitted_color, double light_intensity)
  : Diffuse(albedo, emitted_color * light_intensity) {}