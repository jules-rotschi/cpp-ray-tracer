#include "point3.h"
#include "vector3.h"

Point3::Point3() : x(0), y(0), z(0) {}

Point3::Point3(double x, double y, double z)
  : x(x), y(y), z(z) {}

Point3 operator+(Point3 const &point, Vector3 const &vector) {
  return Point3(point.x + vector.x, point.y + vector.y, point.z + vector.z);
}