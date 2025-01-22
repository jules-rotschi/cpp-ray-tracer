#include "camera.h"

Camera::Camera(int image_width, double image_aspect_ratio)
  : definition({ image_width, int(image_width / image_aspect_ratio) }) {}