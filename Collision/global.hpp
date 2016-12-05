/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw
 * Rev : 2016.12.04.23.40
 * Description : Global header for the whole project, including
 * inclusion of public headers and declarations.
 ************************************************************************/

// Check whether included

#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

// Include public headers

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b);
GLfloat v4Dots(glm::vec4 a,glm::vec4 b);

class Point{
public:
	glm::vec4 vpCoordinate;
	glm::vec4 vpColor;

	Point();
	Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha);
};

class Triangle{
public:
	Point pVertex[3];
	glm::vec4 vNormal_vector;

	Triangle();
	Triangle(Point* a,Point* b,Point* c);
};

class Model
{
public:
    int nLength;
	Triangle* tCone;
	GLfloat fMass,fMomentInertia,fElastic,fVolume;

	Model();
	Model(Model* example);
	~Model(){delete[] tCone;}
};

class Object
{
public:
	Model mStill;
    glm::mat4 mFrame;
    glm::vec3 vSpeed;

	bool Init(int model_type,int material_type,GLfloat vx,GLfloat vy,GLfloat vz);
    void Draw(void);
    void Update(void);
};

extern int nModeltot,nMaterialtot;
extern Model mModellist[100];
extern GLfloat fMateriallist[100][2]; //first is density, second is elasticity
// Declarations of global variables defined in .cpp files

extern int nWindowFlags;
extern int nInitWindowWidth, nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;
extern int nLastClock;

// Declarations of functions

void WindowInit(void);

void OnTimer(int nValue);
void Display(void);

void Game(void);

int main(int argc, char *argv[]);

#endif
