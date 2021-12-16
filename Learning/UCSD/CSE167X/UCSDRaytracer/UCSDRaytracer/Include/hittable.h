#pragma once

#include "globals.h"
#include "ray.h"

struct HitRecord
{
    vec3 hitPoint;
    vec3 normal;
    float intersectDistance;
    bool front_face;

    inline void set_face_normal(const Ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;
};

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(
        const Ray& r, float t_min, float t_max, HitRecord& rec) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;
};

bool HittableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.intersectDistance;
            rec = temp_rec;
        }
    }

    return hit_anything;
}