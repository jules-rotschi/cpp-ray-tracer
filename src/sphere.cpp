#include <iostream>
#include <limits>
#include <cmath>
#include <optional>

#include "sphere.h"
#include "point3.h"
#include "ray.h"
#include "hit.h"
#include "utility.h"
#include "material.h"

Sphere::Sphere(const Point3& position, double radius, const Material& material)
  : m_center(position), m_radius(radius), Object(&material) {}

const Point3& Sphere::get_origin() const {
  return m_center;
}

std::unique_ptr<const Object> Sphere::get_unique_ptr() const {
  return std::make_unique<const Sphere>(*this);
}

bool Sphere:: hit(const Ray& ray, Interval t_interval, Hit& hit_payload) const {
  Vector3 ray_direction = ray.get_direction();
  Vector3 sphere_direction(ray.get_origin(), m_center);
  
  double a = ray_direction.get_squared_length();
  double b = -2 * dot(ray_direction, sphere_direction);
  double c = sphere_direction.get_squared_length() - m_radius * m_radius;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
    return false;

  double discriminant_sqrt = std::sqrt(discriminant);
  
  double t = (-b - discriminant_sqrt) / (2 * a);
  if (!t_interval.contains(t)) {
    t = (-b + discriminant_sqrt) / (2 * a);
    if (!t_interval.contains(t)) return false;
  }
  
  hit_payload.t = t;
  hit_payload.point = ray.at(t);
  Vector3 outward_normal = Vector3(m_center, hit_payload.point) / m_radius;
  hit_payload.set_face_normal(ray, outward_normal);
  hit_payload.material = material;

  return true;
}