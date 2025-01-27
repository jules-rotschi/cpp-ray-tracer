#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vector3.h"

class Ray {
private:
  Point3 m_origin;
  Vector3 m_direction;

public:
  Ray() = delete;
  Ray(const Point3 &origin, const Vector3 &direction);
  Ray(const Point3 &origin, const Point3 &direction);

  const Point3 &get_origin() const;
  const Vector3 &get_direction() const;
  Point3 at(double t) const;
};

#endif