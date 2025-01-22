#ifndef SCENE_H
#define SCENE_H

#include <vector>

class Sphere;
class Camera;

class Scene {
public:
  std::vector<Sphere> spheres;
  void add(Sphere const &sphere);
};

#endif