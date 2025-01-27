#include <iostream>
#include <limits>
#include <cmath>
#include <optional>

#include "sphere.h"
#include "point3.h"
#include "ray.h"

Sphere::Sphere(const Point3 &position, double radius)
  : m_center(position), m_radius(radius) {}

const Point3 &Sphere::get_origin() const {
  return m_center;
}

bool Sphere::hit(const Ray &ray, double ray_tmin, double ray_tmax, HitRecord& hit_record) const {
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
  if (t < ray_tmin || t > ray_tmax) {
    t = (-b + discriminant_sqrt) / (2 * a);
    if (t < ray_tmin || t > ray_tmax) return false;
  }
  
  hit_record.t = t;
  hit_record.point = ray.at(t);
  Vector3 outward_normal = Vector3(m_center, hit_record.point) / m_radius;
  hit_record.set_face_normal(ray, outward_normal);

  return true;
}