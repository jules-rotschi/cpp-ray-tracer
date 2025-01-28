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
  
  Scene scene;

  const Sphere sphere(Point3(0, 0, -5), 1, Color(1, 1, 1));
  scene.add(std::make_shared<Sphere>(sphere));

  const Light light(Point3(-6, 1, -1), Color(1000, 2000, 4000));
  scene.add(std::make_shared<Light>(light));

  const Light back_light(Point3(6, 1, -8), Color(4000, 2000, 1000));
  scene.add(std::make_shared<Light>(back_light));

  const int image_width = 1920;
  const double aspect_ratio = 16.0/9.0;
  const double viewport_height = 0.024;
  const double focal_length = 0.05;
  const double aperture = 2.8;
  const double shutter_speed = 1.0/50;
  const int sensivity = 800;
  const Point3 camera_position = { 0, 0, 0 };

  const Sensor sensor(image_width, aspect_ratio, viewport_height, sensivity);
  const Lens lens = { focal_length, aperture };

  const Camera camera(camera_position, sensor, lens, shutter_speed);

  const Renderer renderer(scene);
  const std::unique_ptr<Image> rendered_image = renderer.render(camera);

  const PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}