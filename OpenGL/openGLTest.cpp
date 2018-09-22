#include <GL/glut.h>
#include <unistd.h>
#include <iostream>

using namespace std;

unsigned int DELAY = 5000000;
float scale = 0.8;
bool scaleUP = false;
bool scaleDown = true;

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex3f(scale, 0.0, scale);
		glVertex3f(scale, 0.0, 0.0);
		glVertex3f(0.0, scale, 0.0);
		glVertex3f(0.0, 0.0, scale);
	glEnd();
	glFlush();

	if( scaleUP ) {
		scale += 0.00001;
		if( scale > 0.8 ) {
			scaleUP = false;
			scaleDown = true;
		}
	} else if ( scaleDown ) {
		scale -= 0.00001;
		if( scale < 0.1 ) {
			scaleDown = false;
			scaleUP = true;
		}
	}
	// if( scale > 0.1 ) {
	// 	scale -= 0.00001;
	// } else {
	// 	scale = 0.1;
	// }
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	while(1) {
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE);
		glutInitWindowSize(400, 300);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("Hello World!");

		//usleep(DELAY);


		glutDisplayFunc(displayMe);
		glutMainLoop();
	}

	return 0;
}