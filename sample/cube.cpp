#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <iterator>
#include <string>

//#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define windowWidth 250
#define windowHeight 250

int x = 0;

void init() 
{ 
	glClearColor (0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0, double(windowWidth) / double(windowHeight), 0.1, 1000.0);
} 

void display() 
{ 
	glClear (GL_COLOR_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(2, 0, 5, 0, 0, 0, 1, 0, 0);
	glRotatef(++x, 1, 0, 0);

	glColor3f (1, 1, 1); 

	glutSolidCube(1.0);

	glutSwapBuffers(); 
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) 
{ 
	switch (key)
	{ 
		case 27: 
		exit(0); 
		break; 
	} 
}

int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize (windowWidth, windowHeight); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("opengl sample"); 
	init (); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard); 
	glutMainLoop(); 
	return 0; 
} 
