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

int main(int argc, char* argv[]) {
  
  Scene scene(Color(30, 40, 60));

  const Sphere ground(Point3(0, -100.5, -5), 100, Color(0.5, 0.5, 0.5));
  scene.add(std::make_shared<Sphere>(ground));

  const Sphere sphere(Point3(0, 0, -5), 0.5, Color(0.5, 0.5, 0.5));
  scene.add(std::make_shared<Sphere>(sphere));

  const Light light(Point3(-6, 1, -1), Color(5000, 5000, 5000));
  scene.add(std::make_shared<Light>(light));

  const Light back_light(Point3(8, 1, -8), Color(8000, 4000, 2000));
  scene.add(std::make_shared<Light>(back_light));

  const int image_width = 1920;
  const double image_aspect_ratio = 16.0/9.0;
  const double viewport_height = 0.024;
  const int sensivity = 800;
  const double focal_length = 0.05;
  const double aperture = 2.8;
  const double shutter_speed = 1.0/50;
  const Point3 camera_position = { 0, 0, 0 };

  const Sensor sensor(image_width, image_aspect_ratio, viewport_height, sensivity);
  const Lens lens = { focal_length, aperture };

  const Camera camera(camera_position, sensor, lens, shutter_speed);

  const int samples_per_pixel = 1000;
  const int depth = 10;

  const Renderer renderer(scene);
  const std::unique_ptr<Image> rendered_image = renderer.render(camera, samples_per_pixel, depth);

  const PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}