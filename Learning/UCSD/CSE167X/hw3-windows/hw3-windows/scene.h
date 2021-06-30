#pragma once

#include <vector>

class Scene
{
public:
	std::vector<float> eyePosition_;
	std::vector<float> corners_;
	int width_;
	int height_;

	Scene();
	Scene(std::vector<float> eyePosition, std::vector<float> corners, int width, int height);
	virtual ~Scene();
};