#include "camera.h"

ImageDefinition::ImageDefinition(int width, double aspect_ratio)
  : width(width), height(width / aspect_ratio) {
    height = height < 1 ? 1 : height;
    this->aspect_ratio = double(width) / height;
}

Sensor::Sensor(int image_width, double image_aspect_ratio, double viewport_height)
  : definition(image_width, image_aspect_ratio) {
    viewport = { viewport_height * definition.aspect_ratio, viewport_height };
  }

double Sensor::get_pixel_dimension() const {
  return viewport.width / definition.width;
}

Camera::Camera(const Sensor &sensor, const Lens &lens, const Point3 &position)
  : sensor(sensor), lens(lens), position(position) {}

double Camera::get_aspect_ratio() const {
  return sensor.definition.aspect_ratio;
}

Point3 Camera::get_pixel_position(int row, int column) const {
  double viewport_begin_x = position.x - sensor.viewport.width / 2;
  double pixel_begin_x = viewport_begin_x + column * sensor.get_pixel_dimension();
  double pixel_center_x = pixel_begin_x + sensor.get_pixel_dimension() / 2;

  double viewport_begin_y = position.y + sensor.viewport.height / 2;
  double pixel_begin_y = viewport_begin_y - row * sensor.get_pixel_dimension();
  double pixel_center_y = pixel_begin_y - sensor.get_pixel_dimension() / 2;

  return Point3(pixel_center_x, pixel_center_y, position.z - lens.focal_length);
}