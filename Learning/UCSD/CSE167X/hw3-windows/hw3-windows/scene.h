#pragma once

#include "transform.h"
#include "geometry.h"
#include "camera.h"

class Scene
{
public:
	Camera camera_;
	Shape* shapes_;
	int numShapes_;

	Scene();
	Scene(Camera, Shape*);
	virtual ~Scene();
};

Vector3 IntersectTest(Scene, Vector3);