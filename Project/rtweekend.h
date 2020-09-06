#pragma once
#ifndef RTWEEKEND_H_INCLUDED
#define RTWEEKEND_H_INCLUDED

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions
inline constexpr double degree_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif
