#include <cmath>
#include "geometry.h"

Materials::Materials()
	: ambient_{0.0f}, diffuse_{ 0.0f }, specular_{ 0.0f }, shininess_{ 0.0f }
{}
Materials::Materials(float ambi, float diff, float spec, float shine)
	: ambient_{ ambi }, diffuse_{ diff }, specular_{ spec }, shininess_{ shine }
{}
Materials::~Materials() {}


//Shape::Shape()
//	: material_{ Materials() }
//{}
//Shape::Shape(Materials m)
//	: material_{ m }
//{}
//Shape::~Shape() {}


Triangle::Triangle() 
	: vertices_ {Vector3(-1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)}
{}
Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c)
	: vertices_{ a, b, c }
{}
Triangle::Triangle(Vector3* vertices)
	: vertices_{ vertices[0], vertices[1], vertices[2] }
{}
Triangle::~Triangle() {}


Sphere::Sphere()
	: center_{ Vector3(0.0f,0.0f,0.0f) }, radius_{ 1.0f }
{}
Sphere::Sphere(Vector3 center, float radius, Materials material)
	: center_{ center }, radius_{ radius }
{}
Sphere::~Sphere() {}

float SphereIntersect(Ray ray, Sphere sphere)
{
	// quadratic equation
	float a = Dot(ray.direction_, ray.direction_);
	float b = 2 * Dot(ray.direction_, ray.origin_ - sphere.center_);
	float c = Dot(ray.origin_ - sphere.center_, ray.origin_ - sphere.center_) - pow(sphere.radius_, 2);

	float discriminant = pow(b,2) - 4 * a * c;
	float t0 = (-b - sqrt(discriminant)) / (2 * a);
	float t1 = (-b + sqrt(discriminant)) / (2 * a);

	// no intersection
	if (discriminant < 0 || a == 0)
		return -1;
	// intersection is tangent
	if (discriminant == 0)
		return t0;
	// return positive intersection
	if (t0 < 0)
		return t1;
	if (t1 < 0)
		return t0;
	// both positive return minimum
	return fmin(t0, t1);
}

