#include "geometry.h"

Materials::Materials()
	: ambient_{0.0f}, diffuse_{ 0.0f }, specular_{ 0.0f }, shininess_{ 0.0f }
{}
Materials::Materials(float ambi, float diff, float spec, float shine)
	: ambient_{ ambi }, diffuse_{ diff }, specular_{ spec }, shininess_{ shine }
{}
Materials::~Materials() {}


Shape::Shape()
	: material_(Materials())
{}
Shape::Shape(Materials m)
	: material_{ m }
{}
Shape::~Shape() {}


Triangle::Triangle() 
	: Shape{ Materials() },
	vertices_ {Vector3(-1.0f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)}
{}
Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c)
	: Shape{ Materials() }, vertices_{ a, b, c }
{}
Triangle::Triangle(Vector3* vertices)
	: Shape{ Materials() }, 
	vertices_{ vertices[0], vertices[1], vertices[2] }
{}
Triangle::~Triangle() {}


Sphere::Sphere()
	: Shape{ Materials() }, center_{ Vector3(0.0f,0.0f,0.0f) }, radius_{ 1.0f }
{}
Sphere::Sphere(Vector3 center, float radius, Materials material)
	: Shape{ material }, center_{ center }, radius_{ radius }
{}
Sphere::~Sphere() {}

Vector3 IntersectTest(Vector3 ray)
{
	return Vector3();
}

