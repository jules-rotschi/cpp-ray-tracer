#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "sphere.h"

class Scene {
public:
  std::vector<Sphere> spheres;
  void add(const Sphere &sphere);
};

#endif