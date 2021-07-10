#pragma once

#include "geometry.h"

// Camera will receive the following inputs from the test files
// lookfromX, lookfromY, lookfromZ
// lookatX, lookatY, lookatZ
// upX, upY, upZ
// fov: field of view in the y direction

class Camera
{
public:
	Vector3 position_;
	Vector3 viewDirection_;
	Vector3 up_;
	float fovy_;

	Camera();
	Camera(Vector3 position, Vector3 viewDirection, Vector3 up, float fovy);
	virtual ~Camera();
};