#pragma once
#include "camera.h"

class Ray
{
public:
	Vector3 origin_;
	Vector3 direction_;
	float intersectPoint = -1.0f;

	Ray();
	Ray(Vector3 orig, Vector3 dir);
	~Ray();
};

Matrix3 LookAt(Camera, Vector3);
Ray GenerateRay(Camera camera, int pixelX, int pixelY);