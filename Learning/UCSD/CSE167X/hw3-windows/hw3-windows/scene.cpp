#include "scene.h"

Scene::Scene()
	: camera_{ Camera() }, spheres_{ nullptr }, numSpheres_{ 0 }, triangles_{ nullptr }, numTriangles_{ 0 }
{}
Scene::Scene(Camera cam, Sphere* spheres, int numSpheres_)
	: camera_{ cam }, spheres_{ spheres }, numSpheres_{ numSpheres_ }
{}
Scene::Scene(Camera cam, Sphere* spheres, int numSpheres_, Triangle* triangles, int numTriangles_)
	: camera_{ cam }, spheres_{ spheres }, numSpheres_{ numSpheres_ }, triangles_{ triangles }, numTriangles_{ numTriangles_ }
{}
Scene::~Scene() {}


bool FindIntersection(Scene scene, Ray ray)
{
	// Test each sphere in the scene
	bool intersectionFound = false;
	for (int i = 0; i < scene.numSpheres_; i++)
	{
		Sphere currentSphere = scene.spheres_[i];
		intersectionFound = SphereIntersect(ray, currentSphere);
	}

	// TODO: Test each triangle in the scene

	return intersectionFound;
}