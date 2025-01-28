#ifndef SPHERE_H
#define SPHERE_H

#include <optional>

class Ray;

#include "point3.h"
#include "object.h"

class Sphere : public Object {
private:
  Point3 m_center;
  double m_radius;

public:
  Sphere() = delete;
  Sphere(const Point3& position, double radius, const Color& color);
  const Point3& get_origin() const;
  bool hit(
    const Ray& ray,
    Interval t_interval,
    HitRecord& hit_record
  ) const override;
};

#endif