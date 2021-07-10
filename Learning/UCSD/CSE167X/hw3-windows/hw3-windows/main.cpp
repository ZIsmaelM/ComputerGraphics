#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "image.h"

const int WIDTH = 100;
const int HEIGHT = 100;

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void display(void)
{
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;

	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("HW3: Ray-Tracer");

	Image foo = Image(WIDTH, HEIGHT, WIDTH * 3, 24);
	int numSamples = foo.width_ * foo.height_;
	uint8_t* pixels = new uint8_t[3 * numSamples];

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// 1) get sample
			// 2) get ray
			// 3) color pixel
		}
	}

	foo.SaveImage("test_image.png", pixels, numSamples);
	delete[] pixels;

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	FreeImage_DeInitialise();

	return 0;
}