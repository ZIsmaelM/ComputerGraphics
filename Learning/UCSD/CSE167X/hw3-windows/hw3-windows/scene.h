#pragma once

#include "transform.h"
#include "geometry.h"
#include "camera.h"

class Scene
{
public:
	Camera camera_;
	Sphere* spheres_;
	int numSpheres_;
	Triangle* triangles_;
	int numTriangles_;

	Scene();
	Scene(Camera, Sphere*, int, Triangle*, int);
	virtual ~Scene();
};

Vector3 FindIntersection(Scene, Ray);