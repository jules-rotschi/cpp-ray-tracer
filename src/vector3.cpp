#include <cmath>

#include "vector3.h"
#include "point3.h"

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(double x, double y, double z)
  : x(x), y(y), z(z) {}

Vector3::Vector3(const Point3 &origin, const Point3 &direction)
  : x(direction.x - origin.x), y(direction.y - origin.y), z(direction.z - origin.z) {}

double Vector3::get_length() const {
  return std::sqrt(get_squared_length());
}

double Vector3::get_squared_length() const {
  return x * x + y * y + z * z;
}

Vector3 Vector3::normalize() const {
  return Vector3(*this / get_length());
}


double dot(const Vector3 &vector1, const Vector3 &vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

Vector3 operator+(Vector3 const &vector1, Vector3 const &vector2) {
  return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 operator*(double t, Vector3 const &vector) {
  return Vector3(t * vector.x, t * vector.y, t * vector.z);
}

Vector3 operator*(Vector3 const &vector, double t) {
  return t * vector;
}

Vector3 operator/(Vector3 const &vector, double t) {
  return (1 / t) * vector;
}

Vector3 operator-(Vector3 const &vector) {
  return -1 * vector;
}