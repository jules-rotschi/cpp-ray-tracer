#include <iostream>
#include <memory>
#include <limits>

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

  double closest_sphere_distance = std::numeric_limits<double>::infinity();
  const Sphere *closest_sphere = nullptr;

  for (const Sphere &sphere : m_scene->spheres) {
    if (sphere.get_closest_intersection(ray).z < closest_sphere_distance) {
      closest_sphere = &sphere;
      closest_sphere_distance = sphere.get_origin().get_distance_from(camera.position);
    }
  }

  double red, green, blue;

  if (closest_sphere) {
    red = 1;
    green = 1;
    blue = 1;
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