#include <iostream>
#include <GL/glut.h>
#include <FreeImage.h>
#include "image.h"

#define WIDTH 600
#define HEIGHT 400

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
	foo.SaveImage("test_image.png");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	FreeImage_DeInitialise();

	return 0;
}