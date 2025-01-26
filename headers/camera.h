#ifndef CAMERA_H
#define CAMERA_H

#include "point3.h"

struct ImageDefinition {
  int width, height;
  double aspect_ratio;
  ImageDefinition() = delete;
  ImageDefinition(int width, double aspect_ratio);
};

struct Viewport {
  double width, height;
};

struct Sensor {
  ImageDefinition definition;
  Viewport viewport;
  // int sensivity;

  Sensor() = delete;
  Sensor(int image_width, double image_aspect_ratio, double viewport_height);
  double get_pixel_dimension() const;
};

struct Lens {
  // const double min_focal_length, max_focal_length;
  double focal_length/*, aperture*/;
};

class Camera {
public:
  Sensor sensor;
  Lens lens;
  Point3 position;
  
  Camera() = delete;
  Camera(const Sensor &sensor, const Lens &lens, const Point3 &position);
  double get_aspect_ratio() const;
  Point3 get_pixel_position(int row, int column) const;
};

#endif