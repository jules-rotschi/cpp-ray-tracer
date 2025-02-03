#include "scene.h"
#include "object.h"

Scene::Scene(Color sky_color) : sky_color(sky_color) {}

void Scene::add(const Object& object) {
  objects.push_back(object.get_unique_ptr());
}

void Scene::add(const Light& light) {
  lights.push_back(std::make_unique<Light>(light));
}