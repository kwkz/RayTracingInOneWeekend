#pragma once
#ifndef HITTABLE_LIST_H_INCLUDED
#define HITTABLE_LIST_H_INCLUDED

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
public:
  hittable_list() = default;
  hittable_list(std::shared_ptr<hittable> object) { add(object); }

  ~hittable_list() = default;

  void clear() { objects_.clear(); }
  void add(std::shared_ptr<hittable> object) { objects_.emplace_back(object); }

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
  std::vector<std::shared_ptr<hittable>> objects_;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  auto closest_so_far = t_max;

  for (const auto& object : objects_) {
    if (object->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }
  return hit_anything;
}
#endif // !HITTABLE_LIST_H_INCLUDED
