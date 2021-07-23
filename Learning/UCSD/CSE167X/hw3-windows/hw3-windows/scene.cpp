#include "scene.h"

Scene::Scene()
	: camera_{ Camera() }, spheres_{ nullptr }, numSpheres_{ 0 }, triangles_{ nullptr }, numTriangles_{ 0 }
{}
Scene::Scene(Camera cam, Sphere* spheres, int numSpheres_, Triangle* triangles, int numTriangles_)
	: camera_{ cam }, spheres_{ spheres }, numSpheres_{ numSpheres_ }, triangles_{ triangles }, numTriangles_{ numTriangles_ }
{}
Scene::~Scene() {}


Vector3 FindIntersection(Scene scene, Ray ray)
{
	// Test each sphere in the scene
	for (int i = 0; i < scene.numSpheres_; i++)
	{
		Sphere currentSphere = scene.spheres_[i];
		float intersectDistance = SphereIntersect(ray, currentSphere);
		if (intersectDistance < 0)
		{
			return Vector3(-1.0f, -1.0f, -1.0f);
		}
	}

	// TODO: Test each triangle in the scene

	return Vector3();
}