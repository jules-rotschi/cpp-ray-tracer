#include <iostream>
#include <memory>

#include "renderer.h"
#include "image.h"
#include "constants.h"
#include "scene.h"
#include "camera.h"

std::shared_ptr<Image> Renderer::render(Camera const &camera) const {
  std::cout << "Rendering image..." << std::endl;

  std::shared_ptr<Image> image = std::make_shared<Image>(1920, 16.0/9.0);

  for (int row = 0; row < image->height; row++) {
    for (int column = 0; column < image->width; column++) {
      
      double red = double(column) / (image->width - 1);
      double green = double(row) / (image->height - 1);
      double blue = 0.0;

      int digital_red = int(255 * red);
      int digital_green = int(255 * green);
      int digital_blue = int(255 * blue);

      PixelColor value = { digital_red, digital_green, digital_blue };
      image->set_pixel(row, column, value);
    }

    std::cout << "\rRemaining lines: " << image->height - row - 1 << std::flush;
  }

  return image;
}

std::shared_ptr<Image> Renderer::render(Scene const &scene, Camera const &camera) const {
  std::cout << "Rendering image..." << std::endl;

  std::shared_ptr<Image> image = std::make_shared<Image>(camera.definition.width, camera.definition.height);

  for (int row = 0; row < image->height; row++) {
    for (int column = 0; column < image->width; column++) {
      
      double red = double(column) / (image->width - 1);
      double green = double(row) / (image->height - 1);
      double blue = 0.0;

      int digital_red = int(255 * red);
      int digital_green = int(255 * green);
      int digital_blue = int(255 * blue);

      PixelColor value = { digital_red, digital_green, digital_blue };
      image->set_pixel(row, column, value);
    }

    std::cout << "\rRemaining lines: " << image->height - row - 1 << std::flush;
  }

  return image;
}