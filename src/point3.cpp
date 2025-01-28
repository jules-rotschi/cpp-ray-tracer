#include "point3.h"
#include "vector3.h"

Point3::Point3() : x(0), y(0), z(0) {}

Point3::Point3(double x, double y, double z)
  : x(x), y(y), z(z) {}

double Point3::get_distance_from(const Point3& point) const {
  return (point - *this).get_length();
}

Point3 operator+(const Point3& point, const Vector3& vector) {
  return Point3(point.x + vector.x, point.y + vector.y, point.z + vector.z);
}

Vector3 operator-(const Point3& point1, const Point3& point2) {
  return Vector3(point2, point1);
}