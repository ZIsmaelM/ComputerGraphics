#pragma once

#include <iostream>
#include "globals.h"
#include "hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(glm::vec3 center, float radius)
		: center(center), radius(radius)
	{};

	virtual bool hit(
		const Ray& r, float minDistance, float maxDistance, HitRecord& rec) const override;

public:
	glm::vec3 center;
	float radius;
	mat4 transform = mat4(1.0);
};

bool Sphere::hit(const Ray& ray, float minDistance, float maxDistance, HitRecord& rec) const
{
	glm::vec3 originToCenter = ray.origin - center;

	float a = dot(ray.direction, ray.direction);
	float b = 2.0 * dot(ray.direction, originToCenter);
	float c = dot(originToCenter, originToCenter) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return false;
	
	float root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root < minDistance || root > maxDistance)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root < minDistance || root > maxDistance)
			return false;
	}

	rec.intersectDistance = root;
	rec.hitPoint = ray.at(root);

	return true;
}

class Triangle : public Hittable
{
public:
	Triangle(glm::vec3 vertexA, glm::vec3 vertexB, glm::vec3 vertexC)
		: vertexA(vertexA), vertexB(vertexB), vertexC(vertexC)
	{};
	virtual bool hit(
		const Ray& r, float minDistance, float maxDistance, HitRecord& rec) const override;

public:
	glm::vec3 vertexA;
	glm::vec3 vertexB;
	glm::vec3 vertexC;
	mat4 transform = mat4(1.0);
};

bool Triangle::hit(const Ray& ray, float minDistance, float maxDistance, HitRecord& rec) const
{
	glm::vec3 edge0 = vertexB - vertexA;
	glm::vec3 edge1 = vertexC - vertexA;
	glm::vec3 normal = cross(edge0, edge1);
	normalize(normal);

	float intersectionDistance = (dot(normal, vertexA) - dot(normal, ray.origin))
		/ dot(normal, ray.direction);

	glm::vec3 intersectionPoint = ray.origin + ray.direction * intersectionDistance;
	glm::vec3 edgeA = cross(vertexB - vertexA, intersectionPoint - vertexA);
	glm::vec3 edgeB = cross(vertexC - vertexB, intersectionPoint - vertexB);
	glm::vec3 edgeC = cross(vertexA - vertexC, intersectionPoint - vertexC);

	if (dot(edgeA, normal) < 0 || dot(edgeB, normal) < 0 || dot(edgeC, normal) < 0)
		return false;
	else
	{
		rec.intersectDistance = intersectionDistance;
		rec.hitPoint = ray.at(intersectionDistance);
		return true;
	}
}