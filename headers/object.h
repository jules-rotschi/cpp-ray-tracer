#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

class Ray;
class Object;
class Material;
class Hit;

#include "interval.h"
#include "color.h"

class Object {
public:
  Object(const Material* material);

  virtual bool hit(
    const Ray& ray,
    Interval t_interval,
    Hit& hit_payload
  ) const = 0;

  virtual std::unique_ptr<const Object> get_unique_ptr() const = 0;

protected:
  const Material* material;
};

#endif