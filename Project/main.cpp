#include "color.h"
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <vector>

int main() {
  constexpr char filename[] = "image.png";

  // image

  constexpr int64_t image_width = 256;
  constexpr int64_t image_height = 256;

  struct pixel {
    pixel() = default;
    pixel(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_  = 255) : r(r_), g(g_), b(b_), a(a_) {}
    unsigned char r{}, g{}, b{}, a{ 255 };
  };

  std::vector<pixel> image;

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
      const color pixel_color(
        static_cast<double>(i) / (image_width - 1),
        static_cast<double>(j) / (image_height - 1),
        0.25);
      image.emplace_back(to_pixel(pixel_color));
    }
  }
  stbi_write_png(filename, static_cast<int>(image_width), static_cast<int>(image_height), static_cast<int>(sizeof(pixel)), image.data(), 0);
  
  std::cerr << "\nDone\n";
}