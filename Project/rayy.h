#pragma once
#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "vec3.h"

class ray {
public:
  ray() = default;
  ray(const point3& origin, const vec3& direction)
    : origin_(origin)
    , direction_(direction_) {}

  point3 origin() const { return origin_; }
  vec3 direction() const { return direction_; }

  point3 at(double t) const {
    return origin_ + t * direction_;
  }

public:
  point3 origin_;
  vec3 direction_;
};

#endif