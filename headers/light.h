#ifndef LIGHT_H
#define LIGHT_H

#include "point3.h"
#include "color.h"

class Light {
public:
  Point3 position;
  Color intensity;
  Light(const Point3& position, const Color& intensity);
};

#endif