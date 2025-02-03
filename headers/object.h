#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

class Ray;
class Object;
class Material;

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
    const Material* material;

    Hit();
    void set_face_normal(const Ray& ray, const Vector3& outward_normal);
  };

class Object {
public:
  Object(const Material* material);

  virtual bool hit(
    const Ray& ray,
    Interval t_interval,
    Hit& hit
  ) const = 0;

  virtual std::unique_ptr<const Object> get_unique_ptr() const = 0;

protected:
  const Material* material;
};

#endif