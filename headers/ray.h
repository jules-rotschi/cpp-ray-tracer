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
  Ray(Point3 const &origin, Vector3 const &direction);
  Ray(Point3 const &origin, Point3 const &direction);

  Point3 at(double t) const;
};

#endif