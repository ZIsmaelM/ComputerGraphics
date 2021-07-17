#include "scene.h"

Scene::Scene()
	: camera_{ Camera() }, shapes_{ nullptr }
{}
Scene::Scene(Camera cam, Shape* shapes)
	: camera_{ cam }, shapes_{ shapes }
{}
Scene::~Scene() {}


Vector3 IntersectTest(Scene scene, Vector3 ray)
{
	// Test each object in the scene
	for (int i = 0; i < scene.numShapes_; i++)
	{
		Shape currentShape = scene.shapes_[i];
		for (int j = 0; j < currentShape.numPrimitives_; j++)
		{
			// TODO: need to check primitive type
		}
	}
}