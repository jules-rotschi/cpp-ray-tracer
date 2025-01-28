#ifndef RENDERER_H
#define RENDERER_H

struct PixelColor;
class Image;
class Scene;
class Camera;
class Color;

class Renderer {
private:
  const Scene* m_scene;
  PixelColor compute_pixel(const Camera& camera, int row, int column) const;
  Color get_pixel(const Camera& camera, const Color& luminance) const;

public:
  Renderer() = delete;
  Renderer(const Scene& scene);
  std::unique_ptr<Image> render(const Camera& camera) const;
};

int digitalize(double value);

#endif