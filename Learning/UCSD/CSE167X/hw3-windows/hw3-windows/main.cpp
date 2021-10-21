#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "globals.h"
//#include "image.h"
#include "geometry.h"
#include "raycaster.h"
#include "scene.h"
#include "shader.h"

const int WIDTH = 10;
const int HEIGHT = 10;
const float ASPECTRATIO = WIDTH / (float)HEIGHT;
const float FOVX = 90.0f;
const float FOVY = 90.0f;

void SaveImage(std::string fname, uint8_t* pixels, int numSamples)
{
	int bytesPerRow = WIDTH * 3;
	int bitsPerPixel = 24;

	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, WIDTH, HEIGHT
		, bytesPerRow, bitsPerPixel, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(FIF_PNG, image, fname.c_str(), 0);
}

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;

	FreeImage_Initialise();

	int numSamples = WIDTH * HEIGHT;
	uint8_t* pixels = new uint8_t[3 * numSamples];
	Vector3 upperLeft	= Vector3(-1, 1, -1);
	Vector3 upperRight	= Vector3(1, 1, -1);
	Vector3 lowerLeft	= Vector3(1, -1, -1);
	Vector3 lowerRight	= Vector3(-1, -1, -1);

	Scene scene = Scene(Vector3(0, 0, 0), upperLeft, upperRight, lowerLeft, lowerRight, WIDTH, HEIGHT);
	Sphere mySphere = Sphere(Vector3(0, 0, -1), 1.f);
	Triangle myTriangle = Triangle(Vector3(-0.5, -0.5, -3), Vector3(0, 0.5, -3), Vector3(0.5, -0.5, -3));

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// 1) get ray
			Ray primaryRay = GenerateRay(scene.eyePosition_, j, i);
			bool rayIntersected = FindIntersection(scene, primaryRay);
			Vector3 color = Vector3(0xFF, 0xFF, 0xFF);
			//if (SphereIntersect(primaryRay, mySphere))
			if (TriangleIntersect(primaryRay, myTriangle))
			{
				color = Vector3(0x00, 0x00, 0xFF);
			}
			// 3) color pixel
			int pixelIndex = (i * WIDTH * 3) + j * 3;
			ColorPixel(pixels, pixelIndex, color);
		}
	}
	SaveImage("test_image.png", pixels, numSamples);
	delete[] pixels;

	FreeImage_DeInitialise();

	return 0;
}