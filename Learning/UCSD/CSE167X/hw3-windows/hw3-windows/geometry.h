#pragma once
#include "transform.h"
#include "raycaster.h"

class Materials
{
public:
	float ambient_;
	float diffuse_;
	float specular_;
	float shininess_;

	Materials();
	Materials(float, float, float, float);
	~Materials();
};

class Shape
{
public:
	Shape* primitives_;
	Materials material_;
	int numPrimitives_;

	Shape();
	Shape(Materials);
	~Shape();
};

class Triangle : public Shape
{
public:
	Vector3 vertices_[3];

	Triangle();
	Triangle(Vector3, Vector3, Vector3);
	Triangle(Vector3*);
	~Triangle();
};

class Sphere : public Shape
{
public:
	Vector3 center_;
	float radius_;

	Sphere();
	Sphere(Vector3, float, Materials);
	~Sphere();
};

Vector3 IntersectTriangle(Vector3, Triangle);
float SphereIntersect(Ray, Sphere);
