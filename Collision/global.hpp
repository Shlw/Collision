/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh
 * Description : Global header for the whole project, including
 * inclusion of public headers and declarations.
 ************************************************************************/

// Check whether included
#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

// Include public headers
#include <cstdlib>
#include <cmath>
#include <climits>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Exception Flags
#define ERROR_UNKNOWN_MODEL 0x0001
#define ERROR_UNKNOWN_MATERIAL 0x0002

// class declarations
class Point;
class Triangle;
class Model;
class Object;

// typedef definitions
typedef glm::vec3* PVec3;
typedef glm::vec4* PVec4;
typedef glm::mat4* PMat4;
typedef Point* PPoint;
typedef Triangle* PTriangle;
typedef Model* PModel;
typedef Object* PObject;

// vector operations
glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b);
float v4Dots(glm::vec4 a,glm::vec4 b);
float v4Length(glm::vec4 a);

// matrix operations
PPoint MultPoint(PMat4 matrix,PPoint p);
PTriangle MultTriangle(PMat4 matrix,PTriangle cone);

// point class represents the still point in local coordinate system
class Point{
public:
    PVec4 vpCoordinate;
    PVec4 vpColor;

    Point();
    Point(PPoint example);
    Point(
        float x,float y,float z,
        float r,float g,float b,float alpha
    );
    ~Point();

    void DrawVertex();
};

// triangle class represents the still triangle(cone) in local coordinate system
class Triangle{
public:
    PPoint pppVertex[3];
    PVec4 vpNormalVector;

    Triangle();
    Triangle(PPoint a,PPoint b,PPoint c);
    Triangle(PPoint a,PPoint b,PPoint c,PVec4 v);
    ~Triangle();

    void Draw();
};

// model class represents the still model in local coordinate system
class Model{
public:
    int nLength; // the number of triangular cones
    PTriangle* tppCone; // the point array of triangle pointers
    float fVolume,fElastic,fMass;

    Model();
    ~Model();

    void Draw();
};

// object class contains
// the matrix(mFrame) to transform between local and global coordinate system
// and several indispensable descriptive aspect of the object
class Object{
public:
    int nModelType;
    PMat4 mpFrame;
    PVec3 vpSpeed;
    float fMomentInertia;

    Object();
    Object(int model,float vx,float vy,float vz);
    ~Object();

    PTriangle IsInside(PPoint tp);

    void Draw();
    void Update();
};

extern int nModelTot;
extern int nObjectTot;
extern PModel mppModelList[100];
extern PObject oppObjectList[100];

// Declarations of global variables defined in .cpp files

// extern int nWindowFlags;
extern int nInitWindowWidth;
extern int nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;

extern double dLastClock, dLastLastClock;
extern double dLastMouseX, dLastMouseY;
extern int npButtonState[3];
extern glm::mat4 mModelTransformMat;

extern float fRotateSpeed;
extern float fTranslateSpeed;
extern float fScrollSpeed;

// Declarations of functions

void ReadFiles();

void WindowInit();
void WindowCleanUp();

void Display(GLFWwindow* w);

void EventInit();
void MouseMotionEvent(GLFWwindow* w, double x, double y);
void MouseWheelEvent(GLFWwindow* w, double x, double y);
void MouseDropEvent(GLFWwindow* w, int c, const char** p);

void Draw();

void Update();

void GameInit();
void Game();

void ModelCleanUp();

int main(int argc, char *argv[]);

#endif
