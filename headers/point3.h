#ifndef POINT3_H
#define POINT3_H

class Vector3;

class Point3 {
public:
  double x, y, z;
  Point3();
  Point3(double x, double y, double z);
  double get_distance_from(const Point3 &point) const;
};

Point3 operator+(Point3 const &point, Vector3 const &vector);

#endif