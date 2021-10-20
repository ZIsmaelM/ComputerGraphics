#include "scene.h"

Scene::Scene(Vector3 eyePos, Vector3 UL, Vector3 UR, Vector3 LL, Vector3 LR, int W, int H)
	: eyePosition_{ eyePos }, imageUpperLeft{ UL }, imageUpperRight{ UR }, imageLowerLeft{ LL }, imageLowerRight{ LR }, imageWidth{ W }, imageHeight{ H }
{}
Scene::~Scene() {}


bool FindIntersection(Scene scene, Ray ray)
{
	// Test each sphere in the scene

	// TODO: Test each triangle in the scene

	return false;
}