#ifndef VECTOR3_H
#define VECTOR3_H

class Point3;

class Vector3 {
public:
  double x, y, z;
  Vector3();
  Vector3(double x, double y, double z);
  Vector3(const Point3 &origin, const Point3 &direction);
  double get_length() const;
  double get_squared_length() const;
  Vector3 normalize() const;
};

double dot(const Vector3 &vector1, const Vector3 &vector2);

Vector3 operator+(const Vector3 &vector1, const Vector3 &vector2);

Vector3 operator*(double t, const Vector3 &vector);
Vector3 operator*(const Vector3 &vector, double t);

Vector3 operator/(const Vector3 &vector, double t);

Vector3 operator-(const Vector3 &vector);

#endif