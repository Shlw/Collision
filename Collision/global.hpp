/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw
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

// class headers
class Point;
class Triangle;
class Model;
class Object;

// typedef headers
typedef Triangle* PTriangle;

// vector operations
glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b);
GLfloat v4Dot(glm::vec4 a,glm::vec4 b);
GLfloat v4Length(glm::vec4 a);

// matrix operations
Point* MultPoint(glm::mat4* matrix,Point* p);
PTriangle MultTriangle(glm::mat4* matrix,PTriangle cone);

// point class represents the still point in local coordinate system
class Point{
public:
	glm::vec4* vpCoordinate;
	glm::vec4* vpColor;

	Point();
	Point(Point* example);
	Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha);
	~Point();
};

// triangle class represents the still triangle(cone) in local coordinate system
class Triangle{
public:
	Point* pVertex[3];
	glm::vec4* vNormal_vector;

	Triangle();
	Triangle(Point* a,Point* b,Point* c);
	~Triangle();
};

// model class represents the still model in local coordinate system
class Model{
public:
    int nLength;  // the number of triangular cones
	PTriangle* tCone;  // the point array of triangle pointers
	GLfloat fVolume;

	Model();
	~Model();
};

// object class contains
// the matrix(mFrame) to transform between local and global coordinate system
// and several indispensable descriptive aspect of the object
class Object{
public:
	int nModeltype;
    glm::mat4* mFrame;
    glm::vec3* vSpeed;
	GLfloat fMomentInertia,fElastic,fMass;

	bool Init(int model_type,int material_type,GLfloat vx,GLfloat vy,GLfloat vz);
	PTriangle Is_inside(Point* tp);
    //void Draw(void);                 //////////ATTENTION!!! need to be re-written
    //void Update(void);               //////////ATTENTION!!! need to be re-written
	Object();
	~Object();
};

extern int nModeltot; // number of model examples
extern int nMaterialtot; // number of material examples
extern Model mModellist[100];
extern GLfloat fMateriallist[100][2]; //first is density, second is elasticity

// Declarations of global variables defined in .cpp files

extern int nWindowFlags;
extern int nInitWindowWidth;
extern int nInitWindowHeight;
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
