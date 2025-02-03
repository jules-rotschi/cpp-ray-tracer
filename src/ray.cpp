#include "ray.h"
#include "vector3.h"

Ray::Ray() : m_origin(0, 0, 0), m_direction(0, 0, 0) {}

Ray::Ray(Point3 const& origin, Vector3 const& direction)
  : m_origin(origin), m_direction(direction) {}

Ray::Ray(Point3 const& origin, Point3 const& direction)
  : m_origin(origin), m_direction(Vector3(origin, direction)) {}

const Point3& Ray::get_origin() const {
  return m_origin;
}

const Vector3& Ray::get_direction() const {
  return m_direction;
}

Point3 Ray::at(double t) const {
  return m_origin + t * m_direction;
}