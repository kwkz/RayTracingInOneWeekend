#include "color.h"
#include "ray.h"
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <vector>

color ray_color(const ray& r) {
  auto unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
  constexpr char filename[] = "image.png";

  // image
  constexpr auto aspect_ratio = 16.0 / 9.0;
  constexpr int64_t image_width = 400;
  constexpr int64_t image_height = static_cast<int>(image_width / aspect_ratio);

  struct pixel {
    pixel() = default;
    pixel(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}
    unsigned char r{}, g{}, b{}, a{ 255 };
  };

  std::vector<pixel> image;

  // camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0f;

  constexpr auto origin = point3();
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // render

  auto to_pixel = [](const color& c) {
    return pixel{
      static_cast<unsigned char>(255.999 * c.x()),
      static_cast<unsigned char>(255.999 * c.y()),
      static_cast<unsigned char>(255.999 * c.z()) };
  };

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto u = static_cast<double>(i) / (image_width - 1);
      auto v = static_cast<double>(j) / (image_height - 1);

      ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      auto pixel_color = ray_color(r);
      image.emplace_back(to_pixel(pixel_color));
    }
  }
  stbi_write_png(filename, static_cast<int>(image_width), static_cast<int>(image_height), static_cast<int>(sizeof(pixel)), image.data(), 0);

  std::cerr << "\nDone\n";
}
