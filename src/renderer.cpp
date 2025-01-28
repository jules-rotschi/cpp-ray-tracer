#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <cmath>

#include "renderer.h"
#include "image.h"
#include "scene.h"
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "ray-tracer.h"
#include "color.h"

Renderer::Renderer(const Scene& scene)
  : m_scene(&scene) {}

std::unique_ptr<Image> Renderer::render(Camera const& camera) const {
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

PixelColor Renderer::compute_pixel(const Camera& camera, int row, int column) const {
  Ray ray(camera.position, camera.get_pixel_position(row, column));

  double ray_tmin = 0;
  double ray_tmax = infinity;

  bool hit = false;
  HitRecord hit_record;
  double closest = ray_tmax;

  for (std::shared_ptr<Object> object : m_scene->objects) {
    if (object->hit(ray, Interval(ray_tmin, closest), hit_record)) {
      hit = true;
      closest = hit_record.t;
    }
  }

  Color illumination(0, 0, 0);

  if (hit) {
    Vector3 unit_ray_direction = Vector3(ray.get_direction()).make_unit();
    for (std::shared_ptr<Light> light : m_scene->lights) {
      Vector3 unit_light_direction = Vector3(hit_record.point, light->position).make_unit();
      double light_distance = hit_record.point.get_distance_from(light->position);
      illumination +=
        light->intensity
        * std::max(-dot(hit_record.unit_normal, unit_light_direction), 0.0)
        / (light_distance * light_distance);
    }
  }
  if (hit) {
    int x = 0;
  }

  Color luminance = illumination * hit_record.albedo / pi;
  Color value = get_pixel(camera, luminance);

  return { digitalize(value.red), digitalize(value.green), digitalize(value.blue) };
}

Color Renderer::get_pixel(const Camera& camera, const Color& luminance) const {
  Color value = luminance * pi * camera.get_exposure() / 0.89;
  value.red = value.red > 1 ? 1 : value.red;
  return value;
}

int digitalize(double value) {
  return int(255 * value);
}