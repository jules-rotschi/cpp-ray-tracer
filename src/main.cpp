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
#include "light.h"
#include "diffuse-material.h"
#include "metallic-material.h"

int main(int argc, char* argv[]) {

  Diffuse grey(Color(0.5, 0.5, 0.5));
  Metallic metallic(Color(0.9, 0.9, 0.9), 0);
  Metallic fuzzy_metallic(Color(0.9, 0.9, 0.9), 0.1);
  
  Scene scene(Color(30, 40, 60));

  const Sphere ground(Point3(0, -100.5, -5), 100, grey);
  scene.add(ground);

  const Sphere center(Point3(0, 0, -5), 0.5, grey);
  scene.add(center);

  const Sphere left(Point3(-1.5, 0, -5), 0.5, metallic);
  scene.add(left);

  const Sphere right(Point3(1.5, 0, -5), 0.5, fuzzy_metallic);
  scene.add(right);

  const Light light(Point3(-6, 1, -1), Color(5000, 5000, 5000));
  scene.add(light);

  const Light back_light(Point3(8, 1, -8), Color(8000, 4000, 2000));
  scene.add(back_light);

  const int image_width = 1920;
  const double image_aspect_ratio = 16.0/9.0;
  const double viewport_height = 0.024;
  const int sensivity = 800;
  const double focal_length = 0.05;
  const double aperture = 4;
  const double shutter_speed = 1.0/50;
  const Point3 camera_position = { 0, 0, 0 };

  const Sensor sensor(image_width, image_aspect_ratio, viewport_height, sensivity);
  const Lens lens = { focal_length, aperture };

  const Camera camera(camera_position, sensor, lens, shutter_speed);

  const int samples_per_pixel = 300;
  const int depth = 10;

  const Renderer renderer(scene);
  const std::unique_ptr<Image> rendered_image = renderer.render(camera, samples_per_pixel, depth);

  // rendered_image->add_glow();

  const PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}