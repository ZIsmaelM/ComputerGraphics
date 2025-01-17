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
#include "hittablelist.h"
#include "Transform.h"
#include "readfile.h"
#include "image.h"

void ColorPixel(Image image, int index, glm::vec3 color)
{
	image.pixels[index] = (uint8_t)color.z;		// Red
	image.pixels[index + 1] = (uint8_t)color.y;	// Green
	image.pixels[index + 2] = (uint8_t)color.x;	// Blue
}

void SaveImage(Image image)
{
	int bytesPerRow = image.width * 3;
	int bitsPerPixel = 24;

	FIBITMAP* imageData = FreeImage_ConvertFromRawBits(image.pixels, image.width, image.height
		, bytesPerRow, bitsPerPixel, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, imageData, image.name.c_str(), 0);
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
		float a = 0xff * record.material.ambient[0];
		float b = 0xff * record.material.ambient[1];
		float c = 0xff * record.material.ambient[2];
		return vec3(a,b,c);
	}

	return backgroundColor;
}

HittableList scene()
{
	HittableList world;
	Sphere foo(vec3(0, 0.75, -1), 0.75);
	Triangle boo(vec3(-1, -2, -1), vec3(1, -2, -1), vec3(0, 0, -1));
	auto b = foo.transform;

	world.add(make_shared<Sphere>(foo));
	world.add(make_shared<Triangle>(boo));

	return world;
}

int main(int argc, char* argv[])
{
	// Initialization
	FreeImage_Initialise();

	// Image
	Image image("test.png", 300, 300, 300 / (float)300, 1, 1);

	// Camera
	Camera camera(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0), 90, image.aspectRatio);

	HittableList world;
	readfile(argv[1], image, camera, world);

	// World
	glm::vec3 backgroundColor(0, 0, 0);
	//world = scene();

	for (int j = image.height - 1; j >= 0; --j)
	{
		for (int i = 0; i < image.width; ++i)
		{
			glm::vec3 color(0x00, 0x00, 0x00);

			for (int s = 0; s < image.samplesPerPixel; ++s)
			{
				float u = i / (float)(image.width - 1);
				float v = j / (float)(image.height - 1);
				
				// Get ray
				Ray ray = camera.get_ray(u, v);


				// Test hit
				vec3 newColor = getPixelColor(ray, world, image.maxDepth);
				color = newColor;
			}

			// set pixel color
			int pixelIndex = (j * image.width * 3) + i * 3;
			ColorPixel(image, pixelIndex, color);
		}
	}
	SaveImage(image);
	delete[] image.pixels;

	FreeImage_DeInitialise();

	return 0;
}