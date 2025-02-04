#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "object.h"

class Scene {
public:
  Color sky_color;
  std::vector<std::unique_ptr<const Object>> objects;
  void add(const Object& object);
  Scene() = delete;
  Scene(Color sky_color);
};

#endif