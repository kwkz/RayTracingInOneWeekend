#pragma once
#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
  sphere() = default;
  sphere(point3 center, double radius) noexcept : center_(center), radius_(radius) {}

  ~sphere() = default;

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
  point3 center_;
  double radius_;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  vec3 oc = r.origin() - center_;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius_ * radius_;
  auto discriminant = half_b * half_b - a * c;

  if (discriminant > 0) {
    auto root = sqrt(discriminant);

    auto temp = (-half_b - root) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.at(rec.t);

      vec3 outward_normal = (rec.p - center_) / radius_;
      rec.set_face_normal(r, outward_normal);
      return true;
    }

    temp = (-half_b + root) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.at(rec.t);

      vec3 outward_normal = (rec.p - center_) / radius_;
      rec.set_face_normal(r, outward_normal);
      return false;
    }
  }
  return false;
}

#endif // !SPHERE_H_INCLUDED
