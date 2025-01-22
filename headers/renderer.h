#ifndef RENDERER_H
#define RENDERER_H

class Image;
class Scene;
class Camera;

class Renderer {
public:
  std::shared_ptr<Image> render(Camera const &camera) const;
  std::shared_ptr<Image> render(Scene const &scene, Camera const &camera) const;
};

#endif