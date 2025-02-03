#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "object.h"
#include "light.h"

class Scene {
public:
  Color sky_color;
  std::vector<std::unique_ptr<const Object>> objects;
  std::vector<std::unique_ptr<const Light>> lights;
  void add(const Object& object);
  void add(const Light& light);
  Scene() = delete;
  Scene(Color sky_color);
};

#endif