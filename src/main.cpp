#include <fstream>
#include <iostream>
#include <memory>

#include "renderer.h"
#include "scene.h"
#include "sphere.h"
#include "image.h"
#include "ppm-encoder.h"
#include "camera.h"
#include "ray.h"
#include "material.h"

int main(int argc, char* argv[]) {

  Diffuse grey(Color(0.5, 0.5, 0.5));
  Diffuse red(Color(0.8, 0.4, 0.4));
  Metallic metallic(Color(0.9, 0.9, 0.9), 0.01);
  Metallic fuzzy_metallic(Color(0.9, 0.9, 0.9), 0.1);
  Emissive white_light(Color(0.1, 0.1, 0.1), Color(1, 1, 1), 30000);
  Emissive warm_light(Color(0.1, 0.1, 0.1), Color(1, 0.5, 0.25), 10000);
  
  Scene scene(Color(10, 14, 20));

  const Sphere ground(Point3(0, -100.5, -5), 100, grey);
  scene.add(ground);

  const Sphere center(Point3(0, 0, -5), 0.5, grey);
  scene.add(center);

  const Sphere back(Point3(-1, 0, -8), 0.5, red);
  scene.add(back);

  const Sphere left(Point3(-1.5, 0, -5), 0.5, metallic);
  scene.add(left);

  const Sphere right(Point3(1.5, 0, -5), 0.5, fuzzy_metallic);
  scene.add(right);

  const Sphere light(Point3(-4, 1, -1), 0.5, white_light);
  scene.add(light);

  const Sphere back_light(Point3(2, 1, -8), 0.5, warm_light);
  scene.add(back_light);

  const int image_width = 1280;
  const double image_aspect_ratio = 16.0/9.0;
  const double viewport_height = 0.024;
  const int sensivity = 800;
  const double focal_length = 0.07;
  const double aperture = 1.4;
  const double focus_distance = 8;
  const double shutter_speed = 1.0/50;
  const Point3 camera_position = { 0, 2, 3 };
  const Vector3 camera_direction = { 0, -1, -5 };
  const Vector3 camera_vup = { 0, 1, 0 };

  const Sensor sensor(image_width, image_aspect_ratio, viewport_height, sensivity);
  const Lens lens(focal_length, aperture, focus_distance);

  Camera camera(camera_position, camera_direction, camera_vup, sensor, lens, shutter_speed);
  camera.add_nd_filter(1.5);

  const int samples_per_pixel = 3000;
  const int depth = 10;

  const Renderer renderer(scene);
  const std::unique_ptr<Image> rendered_image = renderer.render(camera, samples_per_pixel, depth);

  const PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}