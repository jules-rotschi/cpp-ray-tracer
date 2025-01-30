#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"

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

  Sensor() = delete;
  Sensor(int image_width, double image_aspect_ratio, double height, int sensivity);
  double get_pixel_dimension() const;
};

struct Lens {
  double focal_length, aperture;
};

class Camera {
public:
  Point3 position;
  Sensor sensor;
  Lens lens;
  double shutter_speed;
  
  Camera() = delete;
  Camera(const Point3& position, const Sensor& sensor, const Lens& lens, double shutter_speed);
  double get_aspect_ratio() const;
  Point3 get_pixel_position(int row, int column) const;
  double get_exposure() const;
};

Vector3 random_offset();

#endif