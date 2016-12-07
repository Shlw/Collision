/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh
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

// Exception Flags

#define ERROR_UNKNOWN_MODEL 0x0001
#define ERROR_UNKNOWN_MATERIAL 0x0002

class Point;
class Triangle;
class Model;
class Object;

typedef glm::vec3* PVec3;
typedef glm::vec4* PVec4;
typedef glm::mat4* PMat4;
typedef Point* PPoint;
typedef Triangle* PTriangle;
typedef Model* PModel;
typedef Object* PObject;

glm::vec4 v4Cross(glm::vec4 a,glm::vec4 b);
float v4Dots(glm::vec4 a,glm::vec4 b);
float v4Length(glm::vec4 a);

PPoint MultPoint(PMat4 matrix,PPoint p);
PTriangle MultTriangle(PMat4 matrix,PTriangle cone);

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

class Triangle{
public:
    PPoint pppVertex[3];
    PVec4 vpNormalVector;
    
    Triangle();
    Triangle(PPoint a,PPoint b,PPoint c);
    ~Triangle();
    
    void Draw();
};

class Model{
public:
    int nLength;
    PTriangle* tppCone;
    float fVolume;
    
    Model();
    ~Model();
    
    void Draw();
};

class Object{
public:
    int nModelType;
    PMat4 mpFrame;
    PVec3 vpSpeed;
    float fMomentInertia,fElastic,fMass;
    
    Object();
    Object(int model,int material,float vx,float vy,float vz);
    ~Object();
    
    PTriangle IsInside(PPoint tp);
    
    void Draw();
    void Update();
};

extern int nModelTot;
extern int nMaterialTot;
extern int nObjectTot;
extern PModel mppModelList[100];
extern PObject oppObjectList[100];
// first is density, second is elasticity
extern float fppMaterialList[100][2]; 

// Declarations of global variables defined in .cpp files

extern int nWindowFlags;
extern int nInitWindowWidth;
extern int nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;
extern int nLastClock;

// Declarations of functions

void ReadFiles();

void WindowInit();

void OnTimer(int nValue);
void Display();

void Draw();

void Update();

void GameInit();
void Game();

void CleanUp();

int main(int argc, char *argv[]);

#endif
