#ifndef HIT_H
#define HIT_H

class Ray;
class Material;

#include "vector3.h"
#include "point3.h"

class Hit {
public:
  double t = -1;
  Point3 point;
  Vector3 unit_normal;
  bool front_face = false;
  const Material* material = nullptr;

  void set_face_normal(const Ray& ray, const Vector3& outward_normal);
};

#endif