#include <cmath>

#include "material.h"
#include "color.h"
#include "vector3.h"
#include "ray.h"
#include "hit.h"
#include "utility.h"

Material::Material(const Color& albedo, const Color& emitted_color)
  : albedo(albedo), emitted_color(emitted_color) {}

Opaque::Opaque(const Color& albedo, double shine, double roughness)
  : Material(albedo), shine(shine), roughness(roughness) {}

Opaque::Opaque(const Color& albedo, const Color& emitted_color)
  : Material(albedo, emitted_color) {}

bool Opaque::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  Vector3 scattered_direction;

  if (shine > 0 && (shine >= 1 || utility::random() < shine)) {
    Vector3 reflected_direction = incident_ray.get_direction().make_unit().reflect(hit.unit_normal);
    scattered_direction = reflected_direction + roughness * random_unit_vector_in_sphere();
  }
  else {
    scattered_direction = hit.unit_normal + random_unit_vector_in_sphere();
  }
  
  if (scattered_direction.is_nearly_null()) {
    scattered_direction = hit.unit_normal;
  }

  scattered_ray = Ray(hit.point, scattered_direction);
  return true;
}

Emissive::Emissive(const Color& albedo, const Color& emitted_color, double lightness)
  : Opaque(albedo, emitted_color * lightness) {}

Clear::Clear(double refractive_index)
    : refractive_index(refractive_index), Material(Color(1, 1, 1), Color(0, 0, 0)) {
}

bool Clear::scatter(const Ray& incident_ray, const Hit& hit, Ray& scattered_ray) const {
  double first_medium_index = incident_ray.refractive_index;
  double second_medium_index = hit.front_face ? refractive_index : 1;
  double refractive_indices_ratio = first_medium_index / second_medium_index;

  Vector3 incident_unit_vector = incident_ray.get_direction().make_unit();

  double cos_incident_angle = dot(incident_unit_vector, -hit.unit_normal);

  bool ray_only_reflects = refractive_indices_ratio * std::sqrt(1 - cos_incident_angle * cos_incident_angle) > 1;

  double reflectance = (1 - second_medium_index) / (1 + second_medium_index);
  double squared_reflectance = reflectance * reflectance;
  double reflexion_probability =
    squared_reflectance
    + (1 - squared_reflectance)
    * std::pow(1 - cos_incident_angle, 5);

  Vector3 scattered_direction;

  if (ray_only_reflects || utility::random() < reflexion_probability) {
    scattered_direction = incident_unit_vector.reflect(hit.unit_normal);
  } else {
    scattered_direction = incident_unit_vector.refract(hit.unit_normal, refractive_indices_ratio);
  }
  
  scattered_ray = { hit.point, scattered_direction };
  scattered_ray.refractive_index = second_medium_index;
  
  return true;
}