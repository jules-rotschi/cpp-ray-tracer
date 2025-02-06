#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"
#include "vector3.h"

struct ImageDefinition {
  int width, height;
  double aspect_ratio;
  ImageDefinition() = delete;
  ImageDefinition(int width, double aspect_ratio);
};

class Sensor {
private:
  struct SensorDimensions { double width, height; };

public:
  SensorDimensions dimensions;
  ImageDefinition definition;
  int sensivity;
  double gamma;

  Sensor() = delete;
  Sensor(int image_width, double image_aspect_ratio, double height, int sensivity);
};

struct Lens {
  double focal_length, aperture, focus_distance;
  Lens(double focal_length, double aperture, double focus_distance);
};

class Camera {
public:
  Sensor sensor;
  Lens lens;
  
  Camera() = delete;
  Camera(
    const Point3& position,
    const Vector3& lens_direction,
    const Vector3& view_up,
    const Sensor& sensor,
    const Lens& lens,
    double shutter_speed
  );

  void add_nd_filter(double density);
  double get_aspect_ratio() const;
  Point3 get_ray_origin() const;
  Point3 get_virtual_pixel_position(int row, int column) const;
  double get_exposure() const;

private:
  Point3 m_center;
  double m_shutter_speed;
  double m_neutral_density_value;
  Vector3 m_e1, m_e2, m_e3;
};

Vector3 random_offset();

#endif