#pragma once

#include "transform.h"
#include "geometry.h"
#include "camera.h"

class Scene
{
public:
	Vector3 eyePosition_;
	Vector3 imageUpperLeft;
	Vector3 imageUpperRight;
	Vector3 imageLowerLeft;
	Vector3 imageLowerRight;
	int imageHeight;
	int imageWidth;

	Scene(Vector3 eyePos, Vector3 UL, Vector3 UR, Vector3 LL, Vector3 LR, int W, int H);
	virtual ~Scene();
};

bool FindIntersection(Scene, Ray);