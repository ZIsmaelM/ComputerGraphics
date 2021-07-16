#pragma once
#include "geometry.h"
#include "camera.h"

Matrix3 LookAt(Camera);
Vector3 GenerateRay(Camera camera, int pixelX, int pixelY);