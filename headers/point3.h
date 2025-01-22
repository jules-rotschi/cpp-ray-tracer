#ifndef POINT3_H
#define POINT3_H

class Point3 {
public:
  double x, y, z;
  Point3() = default;
  Point3(double x, double y, double z);
};

Point3 operator+(Point3 const &point, Vector3 const &vector);

#endif