#ifndef VECTOR3_H
#define VECTOR3_H

class Point3;

class Vector3 {
public:
  double x, y, z;
  Vector3() = default;
  Vector3(double x, double y, double z);
  Vector3(Point3 origin, Point3 direction);
};

Vector3 operator+(Vector3 const &vector1, Vector3 const &vector2);

Vector3 operator*(double t, Vector3 const &vector);
Vector3 operator*(Vector3 const &vector, double t);

#endif