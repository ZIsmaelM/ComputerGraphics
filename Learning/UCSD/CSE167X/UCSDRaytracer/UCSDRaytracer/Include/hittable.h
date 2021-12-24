#pragma once

#include "globals.h"
#include "ray.h"

struct Material
{
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
};

struct HitRecord
{
    vec3 hitPoint;
    vec3 normal;
    float intersectDistance;
    bool front_face;
    Material material;

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