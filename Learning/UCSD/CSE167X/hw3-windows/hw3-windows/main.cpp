#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "globals.h"
#include "image.h"
#include "geometry.h"
#include "raycaster.h"
#include "scene.h"

const int WIDTH = 100;
const int HEIGHT = 100;
const float FOVX = 90.0f;
const float FOVY = 90.0f;

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;

	FreeImage_Initialise();

	// TODO: placeholder variables that need proper initialization
	Image foo = Image(WIDTH, HEIGHT, WIDTH * 3, 24);
	int numSamples = foo.width_ * foo.height_;
	uint8_t* pixels = new uint8_t[3 * numSamples];
	Camera cam;
	Scene scene;


	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// 1) get ray
			Ray ray = GenerateRay(cam, i, j);
			// 2) get intersection
			Vector3 intersectPoint = FindIntersection(scene, ray);
			// 3) color pixel
		}
	}

	foo.SaveImage("test_image.png", pixels, numSamples);
	delete[] pixels;

	FreeImage_DeInitialise();

	return 0;
}