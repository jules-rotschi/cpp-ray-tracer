#ifndef OBJECT_H
#define OBJECT_H

#include "vector3.h"
#include "point3.h"
#include "ray.h"

class HitRecord {
public:
  double t;
  Point3 point;
  Vector3 normal;
  bool front_face;

  void set_face_normal(const Ray &ray, const Vector3 outward_normal);
};

class Object {
public:
  virtual bool hit(
    const Ray &ray,
    double ray_tmin,
    double ray_tmax,
    HitRecord& hit_record
  ) const = 0;
};

#endif