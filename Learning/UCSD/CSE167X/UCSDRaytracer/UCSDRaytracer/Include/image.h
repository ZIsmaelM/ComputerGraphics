#pragma once
class Image
{
public:
	Image() {};
	Image(std::string name, int w, int h, float aspectRatio, int samplesPerPixel, int maxDepth)
		: name(name), width(w), height(h), aspectRatio(aspectRatio), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth)
	{
		pixels = new uint8_t[3 * width * height];
	};

	virtual ~Image() {};
public:
	std::string name;
	int width;
	int height;
	float aspectRatio;
	int samplesPerPixel;
	int maxDepth;
	uint8_t* pixels;
};