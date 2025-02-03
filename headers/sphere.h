#ifndef SPHERE_H
#define SPHERE_H

#include <optional>
#include <memory>

class Ray;

#include "point3.h"
#include "object.h"

class Sphere : public Object {
private:
  Point3 m_center;
  double m_radius;

public:
  Sphere() = delete;
  Sphere(const Point3& position, double radius, const Material& material);
  const Point3& get_origin() const;
  std::unique_ptr<const Object> get_unique_ptr() const override;
  bool hit(
    const Ray& ray,
    Interval t_interval,
    Hit& hit_payload
  ) const override;
};

#endif