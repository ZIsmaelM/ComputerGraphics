#pragma once

#include <vector>

// Camera will receive the following inputs from the test files
// lookfromX, lookfromY, lookfromZ
// lookatX, lookatY, lookatZ
// upX, upY, upZ
// fov: field of view in the y direction

class Camera
{
public:
	std::vector<float> position_;
	std::vector<float> viewDirection_;
	std::vector<float> up_;
	float fovy_;

	Camera();
	Camera(std::vector<float> position, std::vector<float> viewDirection, std::vector<float> up, float fovy);
	virtual ~Camera();
};