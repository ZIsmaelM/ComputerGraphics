#include <cmath>
#include <iostream>
#include "geometry.h"
#include "globals.h"

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

bool TriangleIntersect(Ray ray, Triangle triangle)
{
	Vector3 v0 = triangle.vertices_[0];
	Vector3 v1 = triangle.vertices_[1];
	Vector3 v2 = triangle.vertices_[2];
	Vector3 dir = ray.direction_;
	Vector3 orig = ray.origin_;

	//// compute plane's normal
	//Vector3 v0v1 = v1 - v0;
	//Vector3 v0v2 = v2 - v0;
	//// no need to normalize
	//Vector3 N = Cross(v0v1, v0v2); // N 
	////float area2 = N.length();

	//// Step 1: finding P

	//// check if ray and plane are parallel ?
	//float NdotRayDirection = Dot(N, dir);
	//if (fabs(NdotRayDirection) < kEpsilon) // almost 0 
	//	return false; // they are parallel so they don't intersect ! 

	//// compute d parameter using equation 2
	//float d = Dot(N,v0);

	//// compute t (equation 3)
	//float t = (Dot(N,orig) + d) / NdotRayDirection;
	//// check if the triangle is in behind the ray
	//if (t < 0) return false; // the triangle is behind 

	//// compute the intersection point using equation 1
	//Vector3 P = orig + dir * t;

	//// Step 2: inside-outside test
	//Vector3 C; // vector perpendicular to triangle's plane 

	//// edge 0
	//Vector3 edge0 = v1 - v0;
	//Vector3 vp0 = P - v0;
	//C = Cross(edge0,vp0);
	//if (Dot(N, C) < 0) return false; // P is on the right side 

	//// edge 1
	//Vector3 edge1 = v2 - v1;
	//Vector3 vp1 = P - v1;
	//C = Cross(edge1,vp1);
	//if (Dot(N, C) < 0)  return false; // P is on the right side 

	//// edge 2
	//Vector3 edge2 = v0 - v2;
	//Vector3 vp2 = P - v2;
	//C = Cross(edge2, vp2);
	//if (Dot(N, C) < 0) return false; // P is on the right side; 

	//return true; // this ray hits the triangle

	std::cout << std::endl;

	// Compute normal
	Vector3 edgeA = triangle.vertices_[1] - triangle.vertices_[0];
	Vector3 edgeB = triangle.vertices_[2] - triangle.vertices_[0];
	Vector3 normal = Cross(edgeA, edgeB);

	// Test if ray & triangle are parallel
	if (Dot(normal, ray.direction_) == 0)
	{
		std::cout << "Parallel" << std::endl;
		return false;
	}

	// Plane equation: Ax + By + Cz + D = 0
	// Ray point: P = Orig + tDir
	float d = Dot(normal, triangle.vertices_[0]);
	float t = (Dot(normal, ray.origin_) + d) / Dot(normal, ray.direction_);
	// return if triangle is behind ray origin (behind eye)
	if (t < 0)
	{
		std::cout << "Behind Camera" << std::endl;
		return false;
	}

	// Inside outside test (This implementation can be made more efficient, but just get it working for now)
	Vector3 p = ray.origin_ + ray.direction_ * t;
	Vector3 edge0 = triangle.vertices_[1] - triangle.vertices_[0];
	Vector3 edge1 = triangle.vertices_[2] - triangle.vertices_[1];
	Vector3 edge2 = triangle.vertices_[0] - triangle.vertices_[2];
	Vector3 edge0ToP = p - edge0;
	Vector3 edge1ToP = p - edge1;
	Vector3 edge2ToP = p - edge2;
	Vector3 cross0 = Cross(edge0, edge0ToP);
	Vector3 cross1 = Cross(edge1, edge1ToP);
	Vector3 cross2 = Cross(edge2, edge2ToP);
	if (Dot(normal, cross0) < 0)
	{
		std::cout << "Cross 0 False" << std::endl;
		return false;
	}
	if (Dot(normal, cross1) < 0)
	{
		std::cout << "Cross 1 False" << std::endl;
		return false;
	}
	if (Dot(normal, cross2) < 0)
	{
		std::cout << "Cross 2 False" << std::endl;
		return false;
	}
	
	return true;

}

Sphere::Sphere()
	: center_{ Vector3(0.0f,0.0f,0.0f) }, radius_{ 1.0f }
{}
Sphere::Sphere(Vector3 center, float radius)
	: center_{ center }, radius_{ radius }
{}
Sphere::~Sphere() {}

bool SphereIntersect(Ray ray, Sphere sphere)
{
	// quadratic equation
	Vector3 length = ray.origin_ - sphere.center_;
	
	float a = Dot(ray.direction_, ray.direction_); // dot(x,x) == 1
	float b = 2.0 * Dot(ray.direction_, length);
	float c = Dot(length, length) - pow(sphere.radius_, 2);

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

