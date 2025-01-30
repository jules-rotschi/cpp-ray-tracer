#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "object.h"
#include "light.h"

class Scene {
public:
  Color sky_color;
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Light>> lights;
  void add(std::shared_ptr<Object> object);
  void add(std::shared_ptr<Light> light);
  Scene() = delete;
  Scene(Color sky_color);
};

#endif