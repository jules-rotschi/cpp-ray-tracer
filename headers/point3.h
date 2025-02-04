#ifndef POINT3_H
#define POINT3_H

class Vector3;

class Point3 {
public:
  double x, y, z;
  Point3();
  Point3(double x, double y, double z);
  double get_distance_from(const Point3& point) const;
};

Point3 operator+(const Point3& point, Vector3 const& vector);
Point3 operator-(const Point3& point, Vector3 const& vector);

Vector3 operator-(const Point3& point1, const Point3& point2);

#endif