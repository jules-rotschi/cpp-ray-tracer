#include <iostream>
#include <memory>
#include <limits>
#include <optional>

#include "renderer.h"
#include "image.h"
#include "constants.h"
#include "scene.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"

int digitalize(double value) {
  return int(255 * value);
}

PixelColor Renderer::compute_pixel(Camera const &camera, int row, int column) const {
  Ray ray(camera.position, camera.get_pixel_position(row, column));

  double ray_tmin = 0;
  double ray_tmax = 1000;

  bool hit = false;
  HitRecord hit_record;
  double closest = ray_tmax;

  for (std::shared_ptr<Object> object : m_scene->objects) {
    if (object->hit(ray, ray_tmin, closest, hit_record)) {
      hit = true;
      closest = hit_record.t;
    }
  }

  double red = 0;
  double green = 0;
  double blue = 0;

  if (hit) {
    Vector3 unit_ray_direction = ray.get_direction().normalize();
    for (std::shared_ptr<Light> light : m_scene->lights) {
      Vector3 light_direction = Vector3(hit_record.point, light->position).normalize();
      red = -dot(hit_record.normal, light_direction);
      green = -dot(hit_record.normal, light_direction);
      blue = -dot(hit_record.normal, light_direction);
      red = red < 0 ? 0 : red;
      green = red < 0 ? 0 : green;
      blue = red < 0 ? 0 : blue;
    }
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  return { digitalize(red), digitalize(green), digitalize(blue) };
}

Renderer::Renderer(const Scene &scene)
  : m_scene(&scene) {}

std::unique_ptr<Image> Renderer::render(Camera const &camera) const {
  std::cout << "Rendering image..." << std::endl;

  std::unique_ptr<Image> image = std::make_unique<Image>(camera.sensor.definition.width, camera.sensor.definition.height);

  for (int row = 0; row < image->height; row++) {
    for (int column = 0; column < image->width; column++) {
      PixelColor pixel_value = compute_pixel(camera, row, column);
      image->set_pixel(row, column, pixel_value);
    }

    std::cout << "\rRemaining lines: " << image->height - row - 1 << std::flush;
  }

  return image;
}