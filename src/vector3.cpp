#include <cmath>

#include "vector3.h"
#include "point3.h"
#include "utility.h"

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(double x, double y, double z)
  : x(x), y(y), z(z) {}

Vector3::Vector3(const Point3& origin, const Point3& direction)
  : x(direction.x - origin.x), y(direction.y - origin.y), z(direction.z - origin.z) {}

bool Vector3::is_nearly_null() const {
  bool x_nearly_null = x * x < 1e-3;
  bool y_nearly_null = y * y < 1e-3;
  bool z_nearly_null = z * z < 1e-3;
  return x_nearly_null && y_nearly_null && z_nearly_null;
}

double Vector3::get_length() const {
  return std::sqrt(get_squared_length());
}

double Vector3::get_squared_length() const {
  return x * x + y * y + z * z;
}

Vector3 Vector3::make_unit() const {
  return *this / get_length();
}

Vector3 Vector3::reflect(const Vector3& normal) const {
  return *this - 2 * dot(*this, normal) * normal;
}

Vector3 Vector3::random() {
  return Vector3(utility::random(), utility::random(), utility::random());
}

Vector3 Vector3::random(double min, double max) {
  return Vector3(utility::random(min, max), utility::random(min, max), utility::random(min, max));
}

double dot(const Vector3& vector1, const Vector3& vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

Vector3 random_unit_vector() {
  while (true) {
    Vector3 random_vector = Vector3::random(-1, 1);
    if (random_vector.get_squared_length() < 1 && random_vector.get_squared_length() > 1e-160) {
      return random_vector.make_unit();
    }
  }
}

Vector3 random_unit_vector_on_hemisphere(const Vector3& hemisphere_direction) {
  Vector3 unit_vector = random_unit_vector();
  if (dot(unit_vector, hemisphere_direction) > 0)
    return unit_vector;
  return -unit_vector;
}

Vector3 operator+(Vector3 const& vector1, Vector3 const& vector2) {
  return Vector3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);
}

Vector3 operator*(double t, Vector3 const& vector) {
  return Vector3(t * vector.x, t * vector.y, t * vector.z);
}

Vector3 operator*(Vector3 const& vector, double t) {
  return t * vector;
}

Vector3 operator/(Vector3 const& vector, double t) {
  return (1 / t) * vector;
}

Vector3& operator/=(Vector3& vector, double t) {
  vector = vector / t;
  return vector;
}

Vector3 operator-(Vector3 const& vector) {
  return -1 * vector;
}

Vector3 operator-(Vector3 const& vector1, const Vector3& vector2) {
  return Vector3(vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z);
}