#ifndef CAMERA_H
#define CAMERA_H

struct ImageDefinition {
  int width, height;
};

class Camera {
public:
  Camera(int image_width, double image_aspect_ratio);
  ImageDefinition definition;
};

#endif