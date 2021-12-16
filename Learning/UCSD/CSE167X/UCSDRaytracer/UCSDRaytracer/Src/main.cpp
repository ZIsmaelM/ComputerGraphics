#include <iostream>

// these defines must be included when using freeglut static
// must be defined before the freeglut include
#define FREEGLUT_STATIC
#define _LIB
#define FREEGLUT_LIB_PRAGMAS 0

#include <glew.h>
#include <glm/glm.hpp>
#include <freeglut.h>


#include "FreeImage.h"
#include "camera.h"
#include "ray.h"
#include "shape.h"
#include "hittable.h"

void ColorPixel(uint8_t* pixels, int index, glm::vec3 color)
{
	pixels[index] = (uint8_t)color.z;		// Red
	pixels[index + 1] = (uint8_t)color.y;	// Green
	pixels[index + 2] = (uint8_t)color.x;	// Blue
}

void SaveImage(std::string fname, uint8_t* pixels, int width, int height)
{
	int bytesPerRow = width * 3;
	int bitsPerPixel = 24;

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height
		, bytesPerRow, bitsPerPixel, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, image, fname.c_str(), 0);
}

vec3 getPixelColor(Ray ray, HittableList world, int depth)
{
	vec3 backgroundColor(0, 0, 0);
	if (depth <= 0) return backgroundColor;

	HitRecord record;
	float minHitDistance = 0.0001;
	float maxHitDistance = INFINITE;
	if (world.hit(ray, minHitDistance, maxHitDistance, record))
	{
		vec3 objectColor(0xFF,0x00,0x00);
		return objectColor;
	}

	return backgroundColor;
}

HittableList scene()
{
	HittableList world;
	world.add(make_shared<Sphere>(vec3(0, 0.75, -1), 0.75));
	world.add(make_shared<Triangle>(vec3(-1, -2, -1), vec3(1, -2, -1), vec3(0, 0, -1)));

	return world;
}

int main()
{
	// Initialization
	FreeImage_Initialise();

	// Image
	int width = 300;
	int height = 300;
	float aspectratio = width / (float)height;
	int samplesPerPixel = 1;
	const int maxDepth = 1;
	// VS really hates this line but my fix breaks the code
	// ....so we'll figure it out later :p
	uint8_t* pixels = new uint8_t[3 * width * height]; 

	// World
	glm::vec3 lookFrom(0,0,1);
	glm::vec3 lookAt(0,0,0);
	float fov = 90;
	glm::vec3 backgroundColor(0, 0, 0);
	HittableList world = scene();

	// Camera
	glm::vec3 up(0, 1, 0);
	camera cam(lookFrom, lookAt, up, fov, aspectratio);

	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			glm::vec3 color(0x00, 0x00, 0x00);

			for (int s = 0; s < samplesPerPixel; ++s)
			{
				float u = i / (float)(width - 1);
				float v = j / (float)(height - 1);
				
				// Get ray
				Ray ray = cam.get_ray(u, v);

				// Test hit
				vec3 newColor = getPixelColor(ray, world, maxDepth);
				color = newColor;
			}

			// set pixel color
			int pixelIndex = (j * width * 3) + i * 3;
			ColorPixel(pixels, pixelIndex, color);
		}
	}
	SaveImage("test_image.png", pixels, width, height);
	delete[] pixels;

	FreeImage_DeInitialise();

	return 0;
}