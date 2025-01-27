#include "object.h"

void HitRecord::set_face_normal(const Ray &ray, const Vector3 outward_normal) {
  front_face = dot(ray.get_direction(), outward_normal) > 0;
  normal = front_face ? outward_normal : -outward_normal;
}