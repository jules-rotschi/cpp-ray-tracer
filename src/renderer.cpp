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
#include "material.h"
#include "hit.h"

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
    Ray ray(camera.get_ray_origin(), camera.get_virtual_pixel_position(row, column));

    Hit hit_payload = trace_ray(ray);
    Color luminance;

    if (hit_payload.t > 0) {
      Color illumination = compute_illumination(ray, hit_payload, depth);
      luminance += illumination * hit_payload.material->albedo / pi;
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

  for (auto& object : m_scene->objects) {
    if (object->hit(ray, Interval(ray_tmin, closest), hit_payload)) {
      closest = hit_payload.t;
    }
  }

  return hit_payload;
}

Color Renderer::compute_illumination(const Ray& incident_ray, const Hit& hit, int depth) const {
  Color own_light = hit.material->emitted_color * pi;
  
  if (depth == 0) return own_light;

  Ray scattered_ray;
  hit.material->scatter(incident_ray, hit, scattered_ray);
  Hit next_hit = trace_ray(scattered_ray);

  if (next_hit.t == -1)
    return own_light + m_scene->sky_color * pi;

  Color direct_illumination = next_hit.material->emitted_color;
  
  return own_light + direct_illumination
    + next_hit.material->albedo
    * compute_illumination(scattered_ray, next_hit, depth - 1);
}

Color Renderer::get_pixel(const Camera& camera, const Color& luminance) const {
  Color linear_value = luminance * pi * camera.get_exposure() / 0.89;
  linear_value.red = linear_value.red > 1 ? 1 : linear_value.red;
  linear_value.green = linear_value.green > 1 ? 1 : linear_value.green;
  linear_value.blue = linear_value.blue > 1 ? 1 : linear_value.blue;
  
  Color gamma_corrected_value;
  gamma_corrected_value.red = std::pow(linear_value.red, camera.sensor.gamma);
  gamma_corrected_value.green = std::pow(linear_value.green, camera.sensor.gamma);
  gamma_corrected_value.blue = std::pow(linear_value.blue, camera.sensor.gamma);
  
  return gamma_corrected_value;
}

int digitalize(double value) {
  return int(255 * value);
}

PixelColor digitalize(Color color) {
  return { digitalize(color.red), digitalize(color.green), digitalize(color.blue) };
}