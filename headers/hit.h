#ifndef HIT_H
#define HIT_H

class Ray;
class Material;

#include "vector3.h"
#include "point3.h"

class Hit {
public:
  double t;
  Point3 point;
  Vector3 unit_normal;
  bool front_face;
  const Material* material;

  Hit();
  void set_face_normal(const Ray& ray, const Vector3& outward_normal);
};

#endif