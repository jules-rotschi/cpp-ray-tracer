#include "scene.h"

Scene::Scene(Color sky_color) : sky_color(sky_color) {}


void Scene::add(std::shared_ptr<Object> object) {
  objects.push_back(object);
}

void Scene::add(std::shared_ptr<Light> light) {
  lights.push_back(light);
}