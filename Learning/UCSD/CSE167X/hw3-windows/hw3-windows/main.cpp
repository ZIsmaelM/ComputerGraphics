#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "globals.h"
#include "image.h"
#include "geometry.h"
#include "raycaster.h"
#include "scene.h"
#include "shader.h"

const int WIDTH = 100;
const int HEIGHT = 100;
const float ASPECTRATIO = WIDTH / HEIGHT;
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
	Camera cam = Camera(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), FOVY);
	
	Sphere sphereList[1];
	Triangle triangleList[1];
	sphereList[0] = Sphere(Vector3(0.0f, 0.0f, -2.0f), 1.0f, Materials());
	triangleList[0] = Triangle();
	Scene scene = Scene(cam, sphereList, 1, triangleList, 0);


	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// 1) get ray
			Ray ray = GenerateRay(cam, i, j);
			Vector3 foo = ray.direction_;
			// 2) get intersection
			Vector3 intersectPoint = FindIntersection(scene, ray);
			Vector3 color = Vector3(0xFF, 0x00, 0x00);
			if (intersectPoint.x_ == -1 && intersectPoint.y_ == -1 && intersectPoint.z_ == -1)
			{
				color = Vector3(0x00, 0x00, 0xff);
			}
			// 3) color pixel
			int pixelIndex = (i * WIDTH * 3) + j * 3;
			ColorPixel(pixels, pixelIndex, color);
		}
	}
	std::cout << "End!\n\n\n\n\n\n\n" << std::endl;
	foo.SaveImage("test_image.png", pixels, numSamples);
	delete[] pixels;

	FreeImage_DeInitialise();

	return 0;
}