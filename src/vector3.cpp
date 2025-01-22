#include "vector3.h"
#include "point3.h"

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(double x, double y, double z)
  : x(x), y(y), z(z) {}

Vector3::Vector3(Point3 origin, Point3 direction)
  : x(direction.x - origin.x), y(direction.y - origin.y), z(direction.z - origin.z) {}

Vector3 operator+(Vector3 const &vector1, Vector3 const &vector2) {
  return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 operator*(double t, Vector3 const &vector) {
  return Vector3(t * vector.x, t * vector.y, t * vector.z);
}

Vector3 operator*(Vector3 const &vector, double t) {
  return t * vector;
}