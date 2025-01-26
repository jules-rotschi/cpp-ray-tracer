#ifndef SPHERE_H
#define SPHERE_H

#include "point3.h"

class Ray;

class Sphere {
private:
  Point3 m_origin;
  double m_radius;

public:
  Sphere() = delete;
  Sphere(const Point3 &position, double radius);
  Point3 get_origin() const;
  Point3 get_closest_intersection(const Ray &ray) const;
};

#endif