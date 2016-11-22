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

int beginX, beginY, dx, dy;
GLfloat rotateX, rotateY;

void init() 
{
	glEnable(GL_LIGHT0);   //new line
	glEnable(GL_LIGHTING);   //new line
	glEnable(GL_DEPTH_TEST);   //new line
	glClearColor (0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0, double(windowWidth) / double(windowHeight), 0.1, 1000.0);
} 

void display() 
{ 
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //editted

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(2, 0, 5, 0, 0, 0, 1, 0, 0);

	glColor3f (1, 1, 1); 

	GLfloat light_position[] = {1.0f, -1.0f, 2.0f, 0.0f};  //new line
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //new line

	float r=1.0, g=1.0, b=1.0;  //new line
	float color[3] = {r, g, b};  //new line

	GLfloat mat_ambient[]  = {r, g, b, 0.5f};  //new line
	GLfloat mat_diffuse[]  = {r, g, b, 0.5f};  //new line
	GLfloat mat_shininess  = 1.0f;  //new line

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  //new line
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);  //new line
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);  //new line

	glRotatef(-rotateY-dy, 0, 1, 0);
	glRotatef(rotateX+dx, 1, 0, 0);

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

void mouseClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		beginX = x;
		beginY = y;
	}
	else
	if (state == GLUT_UP)
	{
		rotateX += dx;
		rotateY += dy;
		dx = dy = 0;
	}
}

void mouseDrag(int x, int y)
{
	dx = x-beginX;
	dy = y-beginY;
}

int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   //editted
	glutInitWindowSize (windowWidth, windowHeight); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("opengl sample (mouse control)"); 
	init (); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseDrag);
	glutMouseFunc(mouseClick);
	glutMainLoop(); 
	return 0; 
} 
