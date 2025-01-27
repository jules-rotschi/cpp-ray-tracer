#ifndef SPHERE_H
#define SPHERE_H

#include <optional>

#include "point3.h"
#include "object.h"

class Ray;

class Sphere : public Object {
private:
  Point3 m_center;
  double m_radius;

public:
  Sphere() = delete;
  Sphere(const Point3 &position, double radius);
  const Point3 &get_origin() const;
  bool hit(
    const Ray &ray,
    double ray_tmin,
    double ray_tmax,
    HitRecord& hit_record
  ) const override;
};

#endif