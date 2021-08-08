#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "globals.h"
//#include "image.h"
#include "geometry.h"
#include "raycaster.h"
#include "scene.h"
#include "shader.h"

const int WIDTH = 200;
const int HEIGHT = 200;
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
	Camera cam = Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 1.0f, 0.0f), FOVY);
	
	Sphere sphereList[1];
	sphereList[0] = Sphere(Vector3(0.0f, 0.0f, 0.0f), 0.1f, Materials());
	Scene scene = Scene(cam, sphereList, 1);


	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// 1) get ray
			Ray primaryRay = GenerateRay(cam, i, j);
			Vector3 foo = primaryRay.direction_;
			// 2) get intersection
			bool rayIntersected = FindIntersection(scene, primaryRay);
			Vector3 color = Vector3(0x00, 0x00, 0x00);
			if (rayIntersected)
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