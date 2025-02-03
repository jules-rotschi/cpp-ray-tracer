#include "object.h"
#include "ray.h"

Hit::Hit() : t(-1) {}

void Hit::set_face_normal(const Ray& ray, const Vector3& outward_normal) {
  front_face = dot(ray.get_direction(), outward_normal) < 0;
  unit_normal = front_face ? outward_normal : -outward_normal;
}

Object::Object(const Material* material) : material(material) {}