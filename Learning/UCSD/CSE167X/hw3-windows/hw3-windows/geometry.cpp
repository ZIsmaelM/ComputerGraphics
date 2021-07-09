#include "geometry.h"

Materials::Materials()
	: ambient_{0.0f}, diffuse_{ 0.0f }, specular_{ 0.0f }, shininess_{ 0.0f }
{}
Materials::Materials(float ambi, float diff, float spec, float shine)
	: ambient_{ ambi }, diffuse_{ diff }, specular_{ spec }, shininess_{ shine }
{}
Materials::~Materials() {}

Triangle::Triangle() 
	: vertices_{ Vector3(-1.0f,0.0f,0.0f), Vector3(1.0f,0.0f,0.0f), Vector3(0.0f,1.0f,0.0f) }
	, material_{ Materials() }
{}

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c)
	: vertices_{ a, b, c }, material_{ Materials() }
{}

Triangle::Triangle(Vector3* vertices)
	: vertices_{ vertices[0], vertices[1], vertices[2] }, material_{ Materials() }
{}

Triangle::~Triangle() {}

Sphere::Sphere()
	: center_{ Vector3(0.0f,0.0f,0.0f) }, radius_{ 1.0f }, material_{ Materials() }
{}

Sphere::Sphere(Vector3 center, float radius, Materials material)
	: center_{ center }, radius_{ radius }, material_{ material }
{}

Sphere::~Sphere() {}

