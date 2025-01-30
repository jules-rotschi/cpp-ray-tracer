#ifndef RENDERER_H
#define RENDERER_H

struct PixelColor;
class Image;
class Scene;
class Camera;
class Color;
class Object;
class Hit;
class Ray;

class Renderer {

private:
  const Scene* m_scene;
  PixelColor compute_pixel(const Camera& camera, int row, int column, int samples_count, int depth) const;
  Hit trace_ray(const Ray& ray) const;
  Color compute_illumination(const Hit& hit, int depth) const;
  Color get_pixel(const Camera& camera, const Color& luminance) const;

public:
  Renderer() = delete;
  Renderer(const Scene& scene);
  std::unique_ptr<Image> render(const Camera& camera, int samples_per_pixel, int depth) const;
};

int digitalize(double value);
PixelColor digitalize(Color value);

#endif