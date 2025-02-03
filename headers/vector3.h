#ifndef VECTOR3_H
#define VECTOR3_H

class Point3;

class Vector3 {
public:
  double x, y, z;

  Vector3();
  Vector3(double x, double y, double z);
  Vector3(const Point3& origin, const Point3& direction);

  bool is_nearly_null() const;
  double get_length() const;
  double get_squared_length() const;
  Vector3 make_unit() const;
  Vector3 reflect(const Vector3& normal) const;
  static Vector3 random();
  static Vector3 random(double min, double max);
};

double dot(const Vector3& vector1, const Vector3& vector2);

Vector3 random_unit_vector();
Vector3 random_unit_vector_on_hemisphere(const Vector3& hemisphere_direction);

Vector3 operator+(const Vector3& vector1, const Vector3& vector2);

Vector3 operator*(double t, const Vector3& vector);
Vector3 operator*(const Vector3& vector, double t);

Vector3 operator/(const Vector3& vector, double t);
Vector3& operator/=(Vector3& vector, double t);

Vector3 operator-(const Vector3& vector);
Vector3 operator-(const Vector3& vector1, const Vector3& vector2);

#endif