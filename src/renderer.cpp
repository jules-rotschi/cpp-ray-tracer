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
#include "utility.h"
#include "color.h"

Renderer::Renderer(const Scene& scene)
  : m_scene(&scene) {}

std::unique_ptr<Image> Renderer::render(Camera const& camera, int samples_per_pixel, int depth) const {
  std::cout << "Rendering image..." << std::endl;

  std::unique_ptr<Image> image =
    std::make_unique<Image>(camera.sensor.definition.width, camera.sensor.definition.height);

  for (int row = 0; row < image->height; row++) {
    for (int column = 0; column < image->width; column++) {
      PixelColor pixel_value = compute_pixel(camera, row, column, samples_per_pixel, depth);
      image->set_pixel(row, column, pixel_value);
    }

    std::cout << "\rRemaining lines: " << image->height - row - 1 << std::flush;
  }

  return image;
}

PixelColor Renderer::compute_pixel(const Camera& camera, int row, int column, int samples_count, int depth) const {
  Color integral_luminance;

  for (int i = 0; i < samples_count; i++) {
    Ray ray(camera.position, camera.get_pixel_position(row, column));

    Hit hit_payload = trace_ray(ray);
    Color luminance;

    if (hit_payload.object) {
      Color illumination = compute_illumination(hit_payload, depth);
      luminance += illumination * hit_payload.object->albedo / pi;
    } else {
      luminance = m_scene->sky_color;
    }
    
    integral_luminance += luminance;
  }

  Color value = get_pixel(camera, integral_luminance / samples_count);

  return digitalize(value);
}

Hit Renderer::trace_ray(const Ray& ray) const {
  double ray_tmin = 1e-3;

  Hit hit_payload;
  double closest = infinity;

  for (std::shared_ptr<Object> object : m_scene->objects) {
    if (object->hit(ray, Interval(ray_tmin, closest), hit_payload)) {
      closest = hit_payload.t;
    }
  }

  return hit_payload;
}

Color Renderer::compute_illumination(const Hit& hit, int depth) const {
  Color direct_illumination;

  for (std::shared_ptr<Light> light : m_scene->lights) {
    Vector3 unit_light_direction = Vector3(hit.point, light->position).make_unit();
    double light_distance = hit.point.get_distance_from(light->position);
    
    direct_illumination +=
      light->intensity
      * std::max(dot(hit.unit_normal, unit_light_direction), 0.0)
      / (light_distance * light_distance);
  }

  if (depth == 0) return direct_illumination;

  Vector3 reflected_direction = random_unit_vector_on_hemisphere(hit.unit_normal);
  Ray reflected_ray(hit.point, reflected_direction);
  Hit next_hit = trace_ray(reflected_ray);

  if (!next_hit.object)
    return direct_illumination + m_scene->sky_color;
  
  return direct_illumination
    + next_hit.object->albedo
    * compute_illumination(next_hit, depth - 1);
}

Color Renderer::get_pixel(const Camera& camera, const Color& luminance) const {
  Color value = luminance * pi * camera.get_exposure() / 0.89;
  value.red = value.red > 1 ? 1 : value.red;
  return value;
}

int digitalize(double value) {
  return int(255 * value);
}

PixelColor digitalize(Color color) {
  return { digitalize(color.red), digitalize(color.green), digitalize(color.blue) };
}