#include <cmath>
#include <numeric>
#include <iostream>
#include "geometry.h"

Materials::Materials()
	: ambient_{0.0f}, diffuse_{ 0.0f }, specular_{ 0.0f }, shininess_{ 0.0f }
{}
Materials::Materials(float ambi, float diff, float spec, float shine)
	: ambient_{ ambi }, diffuse_{ diff }, specular_{ spec }, shininess_{ shine }
{}
Materials::~Materials() {}

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
Sphere::Sphere(Vector3 center, float radius)
	: center_{ center }, radius_{ radius }
{}
Sphere::~Sphere() {}

bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) {
		x0 = x1 = -0.5 * b / a;
	}
	else {
		float q = (b > 0) ?
			-0.5 * (b + (double)sqrt(discr)) :
			-0.5 * (b - (double)sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}

	return true;
}

bool SphereIntersect(Ray ray, Sphere sphere)
{
	// quadratic equation
	Vector3 length = ray.origin_ - sphere.center_;
	
	float a = dot(ray.direction_, ray.direction_); // dot(x,x) == 1
	float b = 2.0 * dot(ray.direction_, length);
	float c = dot(length, length) - pow(sphere.radius_, 2);

	float discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) return false;

	float s = b > 0 ? 1 : -1;
	float t0 = (-b - s * sqrt(discriminant)) / (2 * a);
	float t1 = c / a * t0;

	return (discriminant > 0);
	// no intersection
	if (discriminant < 0 || a == 0)
		return false;
	// intersection is tangent
	else if (discriminant == 0)
		ray.intersectPoint = t0; // t0 should equal (-0.5 * b / a)
	// return positive intersection
	else if (t0 > 0 && t1 > 0)
		ray.intersectPoint = fmin(t0, t1);
	else
		ray.intersectPoint = fmax(t0, t1);

	return true;

}

