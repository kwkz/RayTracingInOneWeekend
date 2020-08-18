#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

int main() {
  constexpr char filename[] = "image.png";

  // image

  constexpr int64_t image_width = 256;
  constexpr int64_t image_height = 256;

  struct pixel {
    pixel() = default;
    unsigned char r{}, g{}, b{}, a{ 255 };
  };

  std::unique_ptr<pixel[][image_width]> data(new pixel[image_height][image_width]);

  // render

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto  r = static_cast<double>(i) / (image_width - 1);
      auto  g = static_cast<double>(j) / (image_height - 1);
      auto  b = 0.25;

      auto& p = data[(image_height - 1) - j][i];
      p.r = static_cast<int>(255.999 * r);
      p.g = static_cast<int>(255.999 * g);
      p.b = static_cast<int>(255.999 * b);

    }
  }
  stbi_write_png(filename, static_cast<int>(image_width), static_cast<int>(image_height), static_cast<int>(sizeof(pixel)), data.get(), 0); 
  
  std::cerr << "\nDone\n";
}