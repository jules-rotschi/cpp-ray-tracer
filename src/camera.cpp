#include <cmath>

#include "camera.h"
#include "vector3.h"
#include "point3.h"
#include "utility.h"

ImageDefinition::ImageDefinition(int width, double aspect_ratio)
  : width(width), height(width / aspect_ratio) {
    height = height < 1 ? 1 : height;
    this->aspect_ratio = double(width) / height;
}

Sensor::Sensor(int image_width, double image_aspect_ratio, double height, int sensivity)
  : definition(image_width, image_aspect_ratio), sensivity(sensivity), gamma(0.45) {
    dimensions = { height * definition.aspect_ratio, height };
  }

Lens::Lens(double focal_length, double aperture, double focus_distance)
  : focal_length(focal_length), aperture(aperture), focus_distance(focus_distance) {}

Camera::Camera(
  const Point3& position,
  const Vector3& lens_direction,
  const Vector3& view_up,
  const Sensor& sensor,
  const Lens& lens,
  double shutter_speed
)
  : m_center(position),
    sensor(sensor),
    lens(lens),
    m_shutter_speed(shutter_speed),
    m_neutral_density_value(0) {
  m_e3 = -lens_direction.make_unit();
  m_e1 = cross(view_up, m_e3).make_unit();
  m_e2 = cross(m_e3, m_e1);
}

void Camera::add_nd_filter(double density) {
  m_neutral_density_value += density;
}

void Camera::remove_nd_filter(double density) {
  if (density <= m_neutral_density_value) {
    m_neutral_density_value -= density;
  }
}

double Camera::get_aspect_ratio() const {
  return sensor.definition.aspect_ratio;
}

Point3 Camera::get_ray_origin() const {
  double aperture_radius = (lens.focal_length / lens.aperture) / 2; 
  return m_center + random_unit_vector_in_disk() * aperture_radius;
}

Point3 Camera::get_virtual_pixel_position(int row, int column) const {
  double viewport_dimension_ratio = lens.focus_distance / lens.focal_length;
  double viewport_width = viewport_dimension_ratio * sensor.dimensions.width;
  double viewport_height = viewport_dimension_ratio * sensor.dimensions.height;

  double pixel_dimension = viewport_width / sensor.definition.width;

  Vector3 offset = random_offset();

  Point3 viewport_begin =
    m_center - (viewport_width / 2) * m_e1 + (viewport_height / 2) * m_e2 - lens.focus_distance * m_e3;

  Point3 pixel_begin =
    viewport_begin + column * pixel_dimension * m_e1 - row * pixel_dimension * m_e2;

  Point3 pixel_center =
    pixel_begin + (pixel_dimension / 2) * (m_e1 - m_e2);

  return pixel_center + offset * pixel_dimension;
}

double Camera::get_exposure() const {
  return sensor.sensivity * m_shutter_speed / (270 * lens.aperture * lens.aperture * std::pow(10, m_neutral_density_value));
}

Vector3 random_offset() {
  return Vector3(0.5 * utility::random(), 0.5 * utility::random(), 0);
}