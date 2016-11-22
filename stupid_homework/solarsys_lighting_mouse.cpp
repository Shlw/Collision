#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <iterator>
#include <string>
//#include <windows.h>

#include <GL/glu.h>
#include <GL/glut.h>

int windowWidth = 1024, windowHeight = 768;
int day = 800;
int nowX,nowY,dx,dy;
GLfloat rotateX,rotateY;
GLfloat cameraX=0,cameraY=-30,cameraZ=15;

void init(){
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, double(windowWidth) / double(windowHeight), 0.1, 1000.0);
}

void drawSphere(float x, float y, double rad, float ang, float r, float g, float b){
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);
	GLfloat light_position[]={-1.0f,0.0f,0.0f,0.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	GLfloat mat_ambient[]={r,g,b,0.5f};
	GLfloat mat_diffuse[]={r,g,b,0.5f};
	GLfloat mat_shininess=0.1f;

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialf(GL_FRONT,GL_SHININESS,mat_shininess);

	glTranslatef(x, y, 0.0f);
	glRotatef(ang, 0, 0, 1);
	//glRotatef(rotateY+dy, 0, 1, 0);
	//glRotatef(rotateX+dx,1 , 0, 0);

	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glutSolidSphere(rad,20,20);

	glColor3f(1-r,1-g,1-b);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glutSolidSphere(rad,20,20);
}

void exchange(double& a,double& b,double c,double d){a=c;b=d;}

void display(){
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	++day;
	static double sunR = 3.5;
	static double earthR = 1;
	static double moonR = 0.4;
	static double earthX=10, earthY=0, moonX=2, moonY=0;
	static double delta_earth=36.0/3650, delta_moon=36.0/300;
	double earthA, moonA, sunA, delta;

	sunA = 360.0/270*(day%270);
	earthA = 360.0/200*(day%200);
	moonA = 360.0/277*(day%277);

	exchange(earthX,earthY,
			 cos(delta_earth)*earthX-sin(delta_earth)*earthY,
			 sin(delta_earth)*earthX+cos(delta_earth)*earthY);
	exchange(moonX,moonY,
			 cos(delta_moon)*moonX-sin(delta_moon)*moonY,
			 sin(delta_moon)*moonX+cos(delta_moon)*moonY);

	cameraX+=dx/3; cameraY+=dy/3;

	drawSphere(0, 0, sunR, sunA, 1, 0, 0);
	drawSphere(earthX, earthY, earthR, earthA, 0, 1, 0);
	drawSphere(moonX+earthX, moonY+earthY, moonR, moonA, 0, 0, 1);


	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y){
	switch (key){
		case 27: exit(0);
		break;
	}
}
void mouseClick(int button,int state,int x,int y){
		if (state==GLUT_DOWN){
			nowX=x;
			nowY=y;
		} else if (state==GLUT_UP){
			rotateX+=dx;
			rotateY+=dy;
			dx=dy=0;
		}
}

void mouseDrag(int x,int y){
	dx=x-nowX;
	dy=y-nowY;
	nowX=x; nowY=y;
}
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Solar System");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseDrag);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;
}
