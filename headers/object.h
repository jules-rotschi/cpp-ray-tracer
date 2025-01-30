#ifndef OBJECT_H
#define OBJECT_H

class Ray;
class Object;

#include "vector3.h"
#include "point3.h"
#include "interval.h"
#include "color.h"

class Hit {
  public:
    double t;
    Point3 point;
    Vector3 unit_normal;
    bool front_face;
    const Object* object;

    Hit();
    void set_face_normal(const Ray& ray, const Vector3& outward_normal);
  };

class Object {
public:
  Color albedo;
  Object(const Color& color);
  virtual bool hit(
    const Ray& ray,
    Interval t_interval,
    Hit& hit
  ) const = 0;
};

#endif