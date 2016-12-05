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

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Class declarations of Model and Object
// **ATTENTION** Public here is convenient but ugly, these classes are
// suggested to be overridden.
// **ATTENTION** Here used glm::vec* and glm::mat* to represent vectors
// and matrices, but frequent construction and destruction which is
// automatically called by the classes may result in low efficiency. Using
// pointers to create instance of these object may be better.

// The class to store models which can be used repeatedly, only storing
// vertices coordinates and colors. The vertices coordinates will be drawn
// with respect to the coordinates of each Object individually.

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b);
GLfloat v4Dots(glm::vec4 a,glm::vec4 b);

class Point{
public:
	glm::vec4* vpCoordinate;
	glm::vec4* vpColor;

	Point():vpCoordinate(NULL),vpColor(NULL){}
	Point(GLfloat x,GLfloat y,GLfloat z,GLfloat r,GLfloat g,GLfloat b,GLfloat alpha){
		vpCoordinate=new glm::vec4(x,y,z,1.0);
		vpColor=new glm::vec4(r,g,b,alpha);
	}
	~Point(){delete vpCoordinate; delete vpColor;}
};

class Triangle{
public:
	Point* pVertex;
	glm::vec4* vNormal_vector;

	Triangle():pVertex(NULL),vNormal_vector(NULL){}
	Triangle(Point* a,Point* b,Point* c){
		pVertex=new Point[3];
		pVertex[0]=*a; pVertex[1]=*b; pVertex[2]=*c;
		vNormal_vector=new glm::vec4(v4Cross(*(b->vpCoordinate)-*(a->vpCoordinate)
								     	   ,*(c->vpCoordinate)-*(b->vpCoordinate)));
	}
	~Triangle(){delete[] pVertex; delete vNormal_vector;}
};

class Model
{
public:
    int nLength;
	Triangle* tCone;
	GLfloat fMass,fMoment_of_inertia,fElastic;

	Model():nLength(0),tCone(NULL),fMass(0),fMoment_of_inertia(0),fElastic(0){}
	~Model(){delete[] tCone;}
};

// The class to store objects, only storing the index of model in the
// mpModelList and the center, the vector of x, y, z-axes and the speed.
// To be exactly, the entries [0][0:2], [1][0:2], [2][0:2] represent the
// vector of x, y, z-axes respectively, and [3][0:2] represent the center
// of the Object, where [i][j] represent the ith row and jth column of the
// matrix and all the coordinates are that in OpenGL global coordinates.
// Each Object use mFrame to establish a new coordinates, and the Model is
// drawn with respect to the new coordinates. Note that the entry [0:2][3]
// must be 0 and the entry [3][3] 1.
// **ATTENTION** glm::mat4 stores in column-major, see glm Manual.
class Object
{
public:
	Model* mStill;
    glm::mat4* mFrame;
    glm::vec3* vSpeed;

	bool init(int num,GLfloat node[][3],int which_type);
    void Draw(void);
    void Update(void);
	Object():mStill(NULL),mFrame(NULL),vSpeed(NULL){}
	~Object(){delete mStill; delete mFrame; delete vSpeed;}
};

// Declarations of global variables defined in .cpp files

extern int nWindowFlags;
extern int nInitWindowWidth, nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;
extern int nLastClock;

// Declarations of Model list and Object lists

extern int nModelCtr;
extern Model mpModelList[30];
extern int nObjectCtr;
extern Object opObjectList[30];

// Declarations of functions

void WindowInit(void);

void OnTimer(int nValue);
void Display(void);

void Game(void);

int main(int argc, char *argv[]);

#endif
