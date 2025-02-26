 #include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "renderer.h"
#include "scene.h"
#include "sphere.h"
#include "image.h"
#include "ppm-encoder.h"
#include "camera.h"
#include "ray.h"
#include "material.h"
#include "plane.h"

constexpr bool PREVIEW = false;

int main(int argc, char* argv[]) {

	// Diffuse colors
  Opaque grey(Color(0.5, 0.5, 0.5), 0, 0);
  Opaque red(Color(0.8, 0.4, 0.4), 0, 0);

  // Metals
  Opaque metal(Color(0.9, 0.9, 0.9), 0.01, 1);
  Opaque fuzzy_metal(Color(0.9, 0.9, 0.9), 0.1, 1);
  
  // Clears
  Clear glass(1.52, Color(0.8, 1, 0.8), 0.1);
  
  // Lights
  Emissive white_light(Color(0.1, 0.1, 0.1), Color(1, 1, 1), 20000);
  Emissive warm_light(Color(0.1, 0.1, 0.1), Color(1, 0.5, 0.25), 20000);
  
  // Shiny
  Opaque ceramic(Color(0.9, 0.9, 0.9), 0.01, 0.5);
  Opaque tiling(Color(0.4, 0.5, 0.5), 0.3, 0.2);
  
  Scene scene(Color(10, 20, 40));

  Sphere tile(Point3(0, -100.5, 0), 100, tiling);
  scene.add(tile);

  Sphere red_sphere(Point3(-1, 0, -2), 0.5, red);
  scene.add(red_sphere);

  Sphere ceramic_sphere(Point3(-1.5, 0, 0), 0.5, ceramic);
  scene.add(ceramic_sphere);

  Sphere metal_sphere(Point3(1.5, 0, -0.5), 0.5, fuzzy_metal);
  scene.add(metal_sphere);

  Sphere glass_sphere(Point3(0, 0, 0), 0.5, glass);
  scene.add(glass_sphere);

  Sphere key_light(Point3(-3, 2, 2), 1, white_light);
  scene.add(key_light);

  Sphere back_light(Point3(3, 150, -150), 50, warm_light);
  scene.add(back_light);

  const int image_width = PREVIEW ? 640 : 1280;
  const double image_aspect_ratio = 16.0/9.0;
  const double viewport_height = 0.024;
  const int sensivity = 800;
  const double focal_length = 0.07;
  const double aperture = 1.4;
  const double focus_distance = 8;
  const double shutter_speed = 1.0/50;
  const Point3 camera_position = { 0, 2, 8 };
  const Vector3 camera_direction = { 0, -1, -5 };
  const Vector3 camera_vup = { 0, 1, 0 };

  const Sensor sensor(image_width, image_aspect_ratio, viewport_height, sensivity);
  const Lens lens(focal_length, aperture, focus_distance);

  Camera camera(camera_position, camera_direction, camera_vup, sensor, lens, shutter_speed);
  camera.add_nd_filter(1.8);

  const int samples_per_pixel = PREVIEW ? 100 : 10000;
  const int depth = PREVIEW ? 10 : 50;

  const Renderer renderer(scene);
  const std::unique_ptr<Image> rendered_image = renderer.render(camera, samples_per_pixel, depth);

  const PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}