#pragma once

#include <glm/glm.hpp>

class ray
{
public:
    ray() {}
    ray(const glm::vec3& origin, const glm::vec3& direction)
        : origin(origin), direction(direction)
    {}

    glm::vec3 getOrigin() const { return origin; }
    glm::vec3 getDirection() const { return direction; }

    glm::vec3 at(float t) const { return origin + direction * t; }

public:
    glm::vec3 origin;
    glm::vec3 direction;
};