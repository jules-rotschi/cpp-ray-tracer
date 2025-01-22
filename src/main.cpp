#include <fstream>
#include <iostream>
#include <memory>

#include "renderer.h"
#include "scene.h"
#include "sphere.h"
#include "image.h"
#include "ppm-encoder.h"
#include "camera.h"

int main(int argc, char *argv[]) {
  
  Scene scene;

  // Sphere sphere;
  // scene.add(sphere);

  Camera camera(1920, 16.0/9.0);

  Renderer renderer;
  std::shared_ptr<Image> rendered_image = renderer.render(scene, camera);

  PpmEncoder encoder;
  std::ofstream output_file("image.ppm");
  encoder.encode(rendered_image, output_file);
  
  return 0;
}