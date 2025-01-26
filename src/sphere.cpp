#include <iostream>
#include <limits>
#include <cmath>

#include "sphere.h"
#include "point3.h"
#include "ray.h"

Sphere::Sphere(const Point3 &position, double radius)
  : m_origin(position), m_radius(radius) {}

Point3 Sphere::get_origin() const {
  return m_origin;
}

Point3 Sphere::get_closest_intersection(const Ray &ray) const {
  Vector3 ray_vector = ray.get_direction();
  Point3 ray_origin = ray.get_origin();
  
  double a = ray_vector.x * ray_vector.x + ray_vector.y * ray_vector.y + ray_vector.z * ray_vector.z;

  double b =
    2 * (
      ray_vector.x * (ray_origin.x - m_origin.x)
      + ray_vector.y * (ray_origin.y - m_origin.y)
      + ray_vector.z * (ray_origin.z - m_origin.z)
      );

  double c =
    ray_origin.x * ray_origin.x - 2 * ray_origin.x * m_origin.x + m_origin.x * m_origin.x
    + ray_origin.y * ray_origin.y - 2 * ray_origin.y * m_origin.y + m_origin.y * m_origin.y
    + ray_origin.z * ray_origin.z - 2 * ray_origin.z * m_origin.z + m_origin.z * m_origin.z
    - m_radius * m_radius;

  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
    return Point3(0, 0, std::numeric_limits<double>::infinity());
  
  double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
  double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

  double t = std::min(t1, t2);

  return ray.at(t);
}