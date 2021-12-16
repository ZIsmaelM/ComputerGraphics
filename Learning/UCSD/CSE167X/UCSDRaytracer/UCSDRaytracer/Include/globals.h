#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

using glm::vec3;
using glm::dot;
using std::shared_ptr;
using std::make_shared;

const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}