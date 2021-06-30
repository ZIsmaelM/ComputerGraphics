#include "scene.h"

Scene::Scene()
	: eyePosition_{ 0.0, 0.0, 0.0 }, corners_{ 0 }, width_{ 600 }, height_{ 400 }
{
}

Scene::Scene(std::vector<float> eyePosition, std::vector<float> corners, int width, int height)
	: eyePosition_{ eyePosition }, corners_{ corners }, width_{ width }, height_{ height }
{
}

Scene::~Scene() {}
