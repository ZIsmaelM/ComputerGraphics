#pragma once

#include <glm/glm.hpp>
#include "globals.h"
#include "ray.h"

class camera
{
public:
    camera(
        glm::vec3 lookfrom,
        glm::vec3 lookat,
        glm::vec3 vup,
        double vfov,    // vertical field of view in degrees
        double aspect_ratio
    )
    {
        auto theta = degreesToRadians(vfov);
        auto h = tan(theta / 2);
        float viewport_height = 2.0 * h;
        float viewport_width = aspect_ratio * viewport_height;

        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = normalize(cross(w, u));

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal * 0.5f - vertical * 0.5f - w;
    }

    ray get_ray(float s, float t) const
    {
        return ray(
            origin,
            lower_left_corner + s * horizontal + t * vertical - origin);
    }

private:
    glm::vec3 origin;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 u, v, w;
};