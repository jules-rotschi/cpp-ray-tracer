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

int main(int argc, char *argv[]) {
  
  Scene scene;

  Sphere sphere(Point3(0, 0, -3), 1);
  scene.add(sphere);

  int image_width = 256;
  double aspect_ratio = 16.0/9.0;
  double viewport_height = 0.024;
  double focal_length = 0.05;
  Point3 camera_position = { 0, 0, 0 };

  Sensor sensor(image_width, aspect_ratio, viewport_height);
  Lens lens = { focal_length };

  Camera camera(sensor, lens, camera_position);

  Renderer renderer(scene);
  std::unique_ptr<Image> rendered_image = renderer.render(camera);

  PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(*rendered_image, output_file);
  
  return 0;
}